#!/usr/bin/env python3
#
# The MIT License (MIT)
#
# Copyright (C) 2026 - EfficiOS, Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# This test reproduces a crash that happened when keys() iterated the
# EVENT_CONTEXT scope of an event with no per-event context.

import bt_python_helper
import tempfile
import babeltrace
import uuid
import shutil


def create_trace(path):
    writer = babeltrace.CTFWriter.Writer(path)
    clock = babeltrace.CTFWriter.Clock('test_clock')
    clock.uuid = uuid.uuid4()
    writer.add_clock(clock)

    int_type = babeltrace.CTFWriter.IntegerFieldDeclaration(32)
    event_class = babeltrace.CTFWriter.EventClass('simple_event')
    event_class.add_field(int_type, 'int_field')

    stream_class = babeltrace.CTFWriter.StreamClass('test_stream')
    stream_class.add_event_class(event_class)
    stream_class.clock = clock

    stream = writer.create_stream(stream_class)

    for i in range(5):
        clock.time = i
        event = babeltrace.CTFWriter.Event(event_class)
        event.payload('int_field').value = i
        stream.append_event(event)

    stream.flush()


def print_test_result(test_number, result, description):
    result_string = 'ok' if result else 'not ok'
    result_string += ' {} - {}'.format(test_number, description)
    print(result_string)


TEST_COUNT = 3

print('1..{}'.format(TEST_COUNT))

trace_path = tempfile.mkdtemp()
print('# Creating trace at {}'.format(trace_path))
create_trace(trace_path)

traces = babeltrace.TraceCollection()
trace_handle = traces.add_trace(trace_path, 'ctf')
print_test_result(1, trace_handle is not None, 'Opening generated trace')

context_fields_ok = True
event_keys_ok = True
event_count = 0

if trace_handle is not None:
    for event in traces.events:
        event_count += 1

        # The crash happened right here.
        context_fields = event.field_list_with_scope(
            babeltrace.CTFScope.EVENT_CONTEXT)
        if context_fields != []:
            print('# Unexpected event context fields: {}'.format(
                context_fields))
            context_fields_ok = False

        keys = event.keys()
        if 'int_field' not in keys:
            print('# Unexpected event keys: {}'.format(keys))
            event_keys_ok = False

print_test_result(2, context_fields_ok,
                  'Missing EVENT_CONTEXT returns an empty field list')
print_test_result(3, event_keys_ok and event_count == 5,
                  'keys() includes payload fields without crashing')

shutil.rmtree(trace_path)

# SPDX-License-Identifier: GPL-2.0-only
# Copyright (C) 2026 EfficiOS Inc.

import typing

import bt2
import pytest


@pytest.fixture
def stream_beginning_msg() -> bt2._StreamBeginningMessage:
    import utils

    return typing.cast(bt2._StreamBeginningMessage, utils.stream_beginning_msg())


@pytest.fixture
def const_stream_beginning_msg() -> bt2._StreamBeginningMessageConst:
    import utils

    return typing.cast(
        bt2._StreamBeginningMessageConst, utils.const_stream_beginning_msg()
    )


@pytest.fixture
def stream_end_msg() -> bt2._StreamEndMessage:
    import utils

    return typing.cast(bt2._StreamEndMessage, utils.stream_end_msg())


@pytest.fixture
def pkt_beginning_msg() -> bt2._PacketBeginningMessage:
    import utils

    return typing.cast(bt2._PacketBeginningMessage, utils.pkt_beginning_msg())


@pytest.fixture
def const_pkt_beginning_msg() -> bt2._PacketBeginningMessageConst:
    import utils

    return typing.cast(
        bt2._PacketBeginningMessageConst, utils.const_pkt_beginning_msg()
    )


@pytest.fixture
def pkt_end_msg() -> bt2._PacketEndMessage:
    import utils

    return typing.cast(bt2._PacketEndMessage, utils.pkt_end_msg())


@pytest.fixture
def ev_msg() -> bt2._EventMessage:
    import utils

    return typing.cast(bt2._EventMessage, utils.ev_msg())


@pytest.fixture
def const_ev_msg() -> bt2._EventMessageConst:
    import utils

    return typing.cast(bt2._EventMessageConst, utils.const_ev_msg())


# Fresh, default trace class.
@pytest.fixture
def def_tc() -> bt2._TraceClass:
    import utils

    return utils.def_tc()

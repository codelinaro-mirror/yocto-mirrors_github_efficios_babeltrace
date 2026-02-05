/*
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Copyright (C) 2020 Philippe Proulx <pproulx@efficios.com>
 */

#include <memory>
#include <utility>

#include <babeltrace2/babeltrace.h>

#include "cpp-common/bt2/graph.hpp"
#include "cpp-common/bt2/mip.hpp"
#include "cpp-common/bt2c/c-string-view.hpp"
#include "cpp-common/bt2c/make-span.hpp"

#include "clk-cls-compat-postconds-triggers.hpp"
#include "fc-tc-match-preconds-triggers.hpp"
#include "utils.hpp"

namespace {

/*
 * Creates a simple condition trigger, calling `func`.
 */
template <typename FuncT>
CondTrigger::UP makeSimpleTrigger(FuncT&& func, const CondTrigger::Type type,
                                  const std::string& condId,
                                  const bt2c::CStringView nameSuffix = {})
{
    return std::make_unique<SimpleCondTrigger>(std::forward<FuncT>(func), type, condId, nameSuffix);
}

bt2::IntegerFieldClass::Shared createUIntFc(const bt2::SelfComponent self)
{
    return self.createTraceClass()->createUnsignedIntegerFieldClass();
}

} /* namespace */

int main(const int argc, const char ** const argv)
{
    CondTriggers triggers;

    triggers.emplace_back(makeSimpleTrigger(
        [] {
            bt2::Graph::create(292);
        },
        CondTrigger::Type::Pre, "graph-create:valid-mip-version"));

    for (std::uint64_t mipVersion = 0; mipVersion < bt2::getMaximalMipVersion(); ++mipVersion) {
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                createUIntFc(self)->fieldValueRange(0);
            },
            CondTrigger::Type::Pre, "field-class-integer-set-field-value-range:valid-n", mipVersion,
            fmt::format("mip{}-0", mipVersion)));

        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                createUIntFc(self)->fieldValueRange(65);
            },
            CondTrigger::Type::Pre, "field-class-integer-set-field-value-range:valid-n", mipVersion,
            fmt::format("mip{}-gt-64", mipVersion)));
    }

    triggers.emplace_back(makeSimpleTrigger(
        [] {
            bt_field_class_integer_set_field_value_range(nullptr, 23);
        },
        CondTrigger::Type::Pre, "field-class-integer-set-field-value-range:not-null:field-class"));

    addClkClsCompatTriggers(triggers);
    addFcTcMatchTriggers(triggers);
    condMain(bt2c::makeSpan(argv, argc), triggers);
}

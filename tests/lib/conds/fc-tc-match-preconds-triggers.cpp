/*
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Copyright (C) 2026 EfficiOS Inc.
 */

#include "cpp-common/bt2/integer-range-set.hpp"
#include "cpp-common/bt2/mip.hpp"
#include "cpp-common/bt2s/span.hpp"
#include "cpp-common/vendor/fmt/core.h"

#include "fc-tc-match-preconds-triggers.hpp"

/*
 * Add triggers for preconditions that verify field class trace class matching.
 *
 * These test two types of preconditions:
 *
 * `fc-has-expected-trace-class`:
 *     Field classes passed to creation functions must have been created from
 *     the specified trace class.
 *
 * `fcs-have-same-trace-class`:
 *     Field classes being combined (e.g., when appending a member to a
 *     structure or an option to a variant) must have been created from the same
 *     trace class.
 */
void addFcTcMatchTriggers(CondTriggers& triggers)
{
    /* Tests valid for all MIP versions */
    for (std::uint64_t mipVersion = 0; mipVersion <= bt2::getMaximalMipVersion(); ++mipVersion) {
        /* bt_field_class_array_static_create: element FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto elemFc = tc1->createUnsignedIntegerFieldClass();

                tc2->createStaticArrayFieldClass(*elemFc, 10);
            },
            CondTrigger::Type::Pre, "field-class-array-static-create:fc-has-expected-trace-class",
            mipVersion, fmt::format("mip{}", mipVersion)));

        /* bt_field_class_structure_append_member: member FC from different TC than struct FC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto structFc = tc1->createStructureFieldClass();
                const auto memberFc = tc2->createUnsignedIntegerFieldClass();

                structFc->appendMember("field", *memberFc);
            },
            CondTrigger::Type::Pre, "field-class-structure-append-member:fcs-have-same-trace-class",
            mipVersion, fmt::format("mip{}", mipVersion)));
    }

    /* Tests valid for MIP 0 only */
    {
        constexpr std::uint64_t mipVersion = 0;

        /* bt_field_class_array_dynamic_create: element FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto elemFc = tc1->createUnsignedIntegerFieldClass();

                tc2->createDynamicArrayFieldClass(*elemFc);
            },
            CondTrigger::Type::Pre, "field-class-array-dynamic-create:fc-has-expected-trace-class",
            mipVersion, "elem-different-tc"));

        /* bt_field_class_array_dynamic_create: length FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto elemFc = tc1->createUnsignedIntegerFieldClass();
                const auto lenFc = tc2->createUnsignedIntegerFieldClass();

                tc1->createDynamicArrayFieldClass(*elemFc, *lenFc);
            },
            CondTrigger::Type::Pre, "field-class-array-dynamic-create:fc-has-expected-trace-class",
            mipVersion, "len-different-tc"));

        /* bt_field_class_option_without_selector_create: optional FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto optFc = tc1->createUnsignedIntegerFieldClass();

                tc2->createOptionFieldClass(*optFc);
            },
            CondTrigger::Type::Pre,
            "field-class-option-without-selector-create:fc-has-expected-trace-class", mipVersion));

        /* bt_field_class_option_with_selector_field_bool_create: optional FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto optFc = tc1->createUnsignedIntegerFieldClass();
                const auto selFc = tc2->createBoolFieldClass();

                tc2->createOptionWithBoolSelectorFieldClass(*optFc, *selFc);
            },
            CondTrigger::Type::Pre,
            "field-class-option-with-selector-field-bool-create:fc-has-expected-trace-class",
            mipVersion, "opt-different-tc"));

        /* bt_field_class_option_with_selector_field_bool_create: selector FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto optFc = tc1->createUnsignedIntegerFieldClass();
                const auto selFc = tc2->createBoolFieldClass();

                tc1->createOptionWithBoolSelectorFieldClass(*optFc, *selFc);
            },
            CondTrigger::Type::Pre,
            "field-class-option-with-selector-field-bool-create:fc-has-expected-trace-class",
            mipVersion, "sel-different-tc"));

        /* bt_field_class_option_with_selector_field_integer_unsigned_create: optional FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto optFc = tc1->createUnsignedIntegerFieldClass();
                const auto selFc = tc2->createUnsignedIntegerFieldClass();
                const auto ranges = bt2::UnsignedIntegerRangeSet::create();

                ranges->addRange(1, 10);
                tc2->createOptionWithUnsignedIntegerSelectorFieldClass(*optFc, *selFc, *ranges);
            },
            CondTrigger::Type::Pre,
            "field-class-option-with-selector-field-integer-unsigned-create:fc-has-expected-trace-class",
            mipVersion, "opt-different-tc"));

        /* bt_field_class_option_with_selector_field_integer_unsigned_create: selector FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto optFc = tc1->createUnsignedIntegerFieldClass();
                const auto selFc = tc2->createUnsignedIntegerFieldClass();
                const auto ranges = bt2::UnsignedIntegerRangeSet::create();

                ranges->addRange(1, 10);
                tc1->createOptionWithUnsignedIntegerSelectorFieldClass(*optFc, *selFc, *ranges);
            },
            CondTrigger::Type::Pre,
            "field-class-option-with-selector-field-integer-unsigned-create:fc-has-expected-trace-class",
            mipVersion, "sel-different-tc"));

        /* bt_field_class_option_with_selector_field_integer_signed_create: optional FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto optFc = tc1->createSignedIntegerFieldClass();
                const auto selFc = tc2->createSignedIntegerFieldClass();
                const auto ranges = bt2::SignedIntegerRangeSet::create();

                ranges->addRange(1, 10);
                tc2->createOptionWithSignedIntegerSelectorFieldClass(*optFc, *selFc, *ranges);
            },
            CondTrigger::Type::Pre,
            "field-class-option-with-selector-field-integer-signed-create:fc-has-expected-trace-class",
            mipVersion, "opt-different-tc"));

        /* bt_field_class_option_with_selector_field_integer_signed_create: selector FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto optFc = tc1->createSignedIntegerFieldClass();
                const auto selFc = tc2->createSignedIntegerFieldClass();
                const auto ranges = bt2::SignedIntegerRangeSet::create();

                ranges->addRange(1, 10);
                tc1->createOptionWithSignedIntegerSelectorFieldClass(*optFc, *selFc, *ranges);
            },
            CondTrigger::Type::Pre,
            "field-class-option-with-selector-field-integer-signed-create:fc-has-expected-trace-class",
            mipVersion, "sel-different-tc"));

        /* bt_field_class_variant_create: selector FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto selFc = tc2->createUnsignedIntegerFieldClass();

                tc1->createVariantWithUnsignedIntegerSelectorFieldClass(*selFc);
            },
            CondTrigger::Type::Pre, "field-class-variant-create:fc-has-expected-trace-class",
            mipVersion));

        /* bt_field_class_variant_without_selector_append_option: option FC from different TC than variant FC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto varFc = tc1->createVariantFieldClass();
                const auto optFc = tc2->createUnsignedIntegerFieldClass();

                varFc->appendOption("opt", *optFc);
            },
            CondTrigger::Type::Pre,
            "field-class-variant-without-selector-append-option:fcs-have-same-trace-class",
            mipVersion));

        /* bt_field_class_variant_with_selector_field_integer_unsigned_append_option: option FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto selFc = tc1->createUnsignedIntegerFieldClass();
                const auto varFc = tc1->createVariantWithUnsignedIntegerSelectorFieldClass(*selFc);
                const auto optFc = tc2->createUnsignedIntegerFieldClass();
                const auto ranges = bt2::UnsignedIntegerRangeSet::create();

                ranges->addRange(1, 10);
                varFc->appendOption("opt", *optFc, *ranges);
            },
            CondTrigger::Type::Pre,
            "field-class-variant-with-selector-field-integer-unsigned-append-option:fcs-have-same-trace-class",
            mipVersion));

        /* bt_field_class_variant_with_selector_field_integer_signed_append_option: option FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto selFc = tc1->createSignedIntegerFieldClass();
                const auto varFc = tc1->createVariantWithSignedIntegerSelectorFieldClass(*selFc);
                const auto optFc = tc2->createSignedIntegerFieldClass();
                const auto ranges = bt2::SignedIntegerRangeSet::create();

                ranges->addRange(1, 10);
                varFc->appendOption("opt", *optFc, *ranges);
            },
            CondTrigger::Type::Pre,
            "field-class-variant-with-selector-field-integer-signed-append-option:fcs-have-same-trace-class",
            mipVersion));
    }

    /* Tests valid for MIP 1+ only */
    for (std::uint64_t mipVersion = 1; mipVersion <= bt2::getMaximalMipVersion(); ++mipVersion) {
        /* bt_field_class_array_dynamic_without_length_field_location_create: element FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto elemFc = tc1->createUnsignedIntegerFieldClass();

                tc2->createDynamicArrayWithoutLengthFieldLocationFieldClass(*elemFc);
            },
            CondTrigger::Type::Pre,
            "field-class-array-dynamic-without-length-field-location-create:fc-has-expected-trace-class",
            mipVersion, fmt::format("mip{}", mipVersion)));

        /* bt_field_class_option_without_selector_field_location_create: optional FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto optFc = tc1->createUnsignedIntegerFieldClass();

                tc2->createOptionWithoutSelectorFieldLocationFieldClass(*optFc);
            },
            CondTrigger::Type::Pre,
            "field-class-option-without-selector-field-location-create:fc-has-expected-trace-class",
            mipVersion, fmt::format("mip{}", mipVersion)));

        /* bt_field_class_option_with_selector_field_location_bool_create: optional FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto optFc = tc1->createUnsignedIntegerFieldClass();
                const char *items[] = {"len"};
                const auto fl =
                    tc2->createFieldLocation(bt2::ConstFieldLocation::Scope::PacketContext,
                                             bt2s::span<const char * const> {items, 1});

                tc2->createOptionWithBoolSelectorFieldLocationFieldClass(*optFc, *fl);
            },
            CondTrigger::Type::Pre,
            "field-class-option-with-selector-field-location-bool-create:fc-has-expected-trace-class",
            mipVersion, fmt::format("mip{}", mipVersion)));

        /* bt_field_class_option_with_selector_field_location_integer_unsigned_create: optional FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto optFc = tc1->createUnsignedIntegerFieldClass();
                const char *items[] = {"sel"};
                const auto fl =
                    tc2->createFieldLocation(bt2::ConstFieldLocation::Scope::PacketContext,
                                             bt2s::span<const char * const> {items, 1});
                const auto ranges = bt2::UnsignedIntegerRangeSet::create();

                ranges->addRange(1, 10);
                tc2->createOptionWithUnsignedIntegerSelectorFieldLocationFieldClass(*optFc, *fl,
                                                                                    *ranges);
            },
            CondTrigger::Type::Pre,
            "field-class-option-with-selector-field-location-integer-unsigned-create:fc-has-expected-trace-class",
            mipVersion, fmt::format("mip{}", mipVersion)));

        /* bt_field_class_option_with_selector_field_location_integer_signed_create: optional FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto optFc = tc1->createSignedIntegerFieldClass();
                const char *items[] = {"sel"};
                const auto fl =
                    tc2->createFieldLocation(bt2::ConstFieldLocation::Scope::PacketContext,
                                             bt2s::span<const char * const> {items, 1});
                const auto ranges = bt2::SignedIntegerRangeSet::create();

                ranges->addRange(1, 10);
                tc2->createOptionWithSignedIntegerSelectorFieldLocationFieldClass(*optFc, *fl,
                                                                                  *ranges);
            },
            CondTrigger::Type::Pre,
            "field-class-option-with-selector-field-location-integer-signed-create:fc-has-expected-trace-class",
            mipVersion, fmt::format("mip{}", mipVersion)));

        /* bt_field_class_array_dynamic_with_length_field_location_create: element FC from different TC */
        triggers.emplace_back(makeRunInCompInitTrigger(
            [](const bt2::SelfComponent self) {
                const auto tc1 = self.createTraceClass();
                const auto tc2 = self.createTraceClass();
                const auto elemFc = tc1->createUnsignedIntegerFieldClass();
                const char *items[] = {"len"};
                const auto fl =
                    tc2->createFieldLocation(bt2::ConstFieldLocation::Scope::PacketContext,
                                             bt2s::span<const char * const> {items, 1});

                tc2->createDynamicArrayWithLengthFieldLocationFieldClass(*elemFc, *fl);
            },
            CondTrigger::Type::Pre,
            "field-class-array-dynamic-with-length-field-location-create:fc-has-expected-trace-class",
            mipVersion, fmt::format("mip{}", mipVersion)));
    }
}

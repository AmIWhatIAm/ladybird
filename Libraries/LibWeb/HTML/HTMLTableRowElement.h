/*
 * Copyright (c) 2020, Andreas Kling <andreas@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/ARIA/Roles.h>
#include <LibWeb/HTML/HTMLElement.h>

namespace Web::HTML {

class HTMLTableRowElement final : public HTMLElement {
    WEB_PLATFORM_OBJECT(HTMLTableRowElement, HTMLElement);
    GC_DECLARE_ALLOCATOR(HTMLTableRowElement);

public:
    virtual ~HTMLTableRowElement() override;

    GC::Ref<DOM::HTMLCollection> cells() const;

    int row_index() const;
    int section_row_index() const;
    WebIDL::ExceptionOr<GC::Ref<HTMLTableCellElement>> insert_cell(i32 index);
    WebIDL::ExceptionOr<void> delete_cell(i32 index);

    // https://www.w3.org/TR/html-aria/#el-tr
    virtual Optional<ARIA::Role> default_role() const override { return ARIA::Role::row; }

private:
    HTMLTableRowElement(DOM::Document&, DOM::QualifiedName);

    virtual bool is_html_table_row_element() const override { return true; }

    virtual void initialize(JS::Realm&) override;
    virtual void visit_edges(Cell::Visitor&) override;
    virtual bool is_presentational_hint(FlyString const&) const override;
    virtual void apply_presentational_hints(GC::Ref<CSS::CascadedProperties>) const override;

    GC::Ptr<DOM::HTMLCollection> mutable m_cells;
};

}

namespace Web::DOM {
template<>
inline bool Node::fast_is<HTML::HTMLTableRowElement>() const { return is_html_table_row_element(); }
}

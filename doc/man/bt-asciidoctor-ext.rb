# SPDX-FileCopyrightText: 2026 Philippe Proulx <pproulx@efficios.com>
# SPDX-License-Identifier: MIT

# Asciidoctor extensions for the Babeltrace 2 manual pages.
#
# Sources use the standard Asciidoctor inline-macro form
# `name:target[attrlist]`. Macros that emit monospaced text do so via
# the `:quoted` semantic node so the backend (docbook5 for the man
# page build) picks the right markup (`<literal>` / `<code>` / ...).
# `man:` emits DocBook-specific `<citerefentry>` on docbook5 and falls
# back to bold "page(N)" on other backends, since there is no
# cross-backend equivalent.

require 'asciidoctor/extensions'

module Babeltrace2ManExt
  class ManInlineMacro < Asciidoctor::Extensions::InlineMacroProcessor
    use_dsl
    named :man
    def process(parent, target, attrs)
      if parent.document.backend == 'docbook5'
        create_inline_pass parent,
          %(<citerefentry><refentrytitle>#{target}</refentrytitle>) +
          %(<manvolnum>#{attrs[1]}</manvolnum></citerefentry>)
      else
        create_inline parent, :quoted, "#{target}(#{attrs[1]})",
                      type: :strong
      end
    end
  end

  class OptInlineMacro < Asciidoctor::Extensions::InlineMacroProcessor
    use_dsl
    named :opt
    def process(parent, target, attrs)
      create_inline parent, :quoted, target, type: :monospaced
    end
  end

  class NloptInlineMacro < Asciidoctor::Extensions::InlineMacroProcessor
    use_dsl
    named :nlopt
    def process(parent, target, attrs)
      create_inline parent, :quoted, target, type: :monospaced
    end
  end

  class ManoptInlineMacro < Asciidoctor::Extensions::InlineMacroProcessor
    use_dsl
    named :manopt
    def process(parent, target, attrs)
      create_inline parent, :quoted, attrs[2], type: :monospaced
    end
  end

  class ParamInlineMacro < Asciidoctor::Extensions::InlineMacroProcessor
    use_dsl
    named :param
    def process(parent, target, attrs)
      create_inline parent, :quoted, target, type: :monospaced
    end
  end

  class NlparamInlineMacro < Asciidoctor::Extensions::InlineMacroProcessor
    use_dsl
    named :nlparam
    def process(parent, target, attrs)
      create_inline parent, :quoted, target, type: :monospaced
    end
  end

  class ManparamInlineMacro < Asciidoctor::Extensions::InlineMacroProcessor
    use_dsl
    named :manparam
    def process(parent, target, attrs)
      create_inline parent, :quoted, attrs[1], type: :monospaced
    end
  end

  class QresInlineMacro < Asciidoctor::Extensions::InlineMacroProcessor
    use_dsl
    named :qres
    def process(parent, target, attrs)
      create_inline parent, :quoted, target, type: :monospaced
    end
  end

  class NlqresInlineMacro < Asciidoctor::Extensions::InlineMacroProcessor
    use_dsl
    named :nlqres
    def process(parent, target, attrs)
      create_inline parent, :quoted, target, type: :monospaced
    end
  end

  class CompclsInlineMacro < Asciidoctor::Extensions::InlineMacroProcessor
    use_dsl
    named :compcls
    def process(parent, target, attrs)
      create_inline parent, :quoted, target, type: :monospaced
    end
  end

  class VtypeInlineMacro < Asciidoctor::Extensions::InlineMacroProcessor
    use_dsl
    named :vtype
    format :short
    def process(parent, target, attrs)
      create_inline_pass parent, %([#{attrs[1]}])
    end
  end
end

# Disambiguation: Asciidoctor's default inline-macro pattern has no
# leading word boundary, so `opt:--x[]` would also match inside
# `nlopt:--x[]` and `manopt:page[1,--x]`. Inline macros run in
# registration order and each pass operates on the text already
# rewritten by previous passes, so registering the longer-prefix names
# first lets them consume their text before the shorter-name processors
# can mis-match into it. (`man:` is *not* a substring of `manopt:` or
# `manparam:`, so it doesn't need similar handling.)
Asciidoctor::Extensions.register do
  inline_macro Babeltrace2ManExt::NloptInlineMacro
  inline_macro Babeltrace2ManExt::ManoptInlineMacro
  inline_macro Babeltrace2ManExt::OptInlineMacro
  inline_macro Babeltrace2ManExt::NlparamInlineMacro
  inline_macro Babeltrace2ManExt::ManparamInlineMacro
  inline_macro Babeltrace2ManExt::ParamInlineMacro
  inline_macro Babeltrace2ManExt::NlqresInlineMacro
  inline_macro Babeltrace2ManExt::QresInlineMacro
  inline_macro Babeltrace2ManExt::ManInlineMacro
  inline_macro Babeltrace2ManExt::CompclsInlineMacro
  inline_macro Babeltrace2ManExt::VtypeInlineMacro
end

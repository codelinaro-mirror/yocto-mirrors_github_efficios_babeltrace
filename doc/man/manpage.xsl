<?xml version='1.0'?>

<!--
SPDX-FileCopyrightText: 2017 Philippe Proulx <pproulx@efficios.com>
SPDX-License-Identifier: CC-BY-SA-4.0
-->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <!--
    Import the namespaced DocBook XSL manpages stylesheet.

    The URL is resolved by the system's XML catalog to a locally
    installed copy of the namespaced DocBook XSL stylesheets.

    The non-namespaced variant (which xmlto selects by default) strips
    the DocBook namespace by rebuilding the input as a result tree
    fragment, and the `xsl:strip-space` declarations baked into the
    DocBook XSL don't apply to that rebuilt tree. That would leave
    inter-element whitespace as blank lines in the generated roff.

    This is a known, long-standing interaction between xmlto (which
    hardcodes the non-namespaced stylesheet URI in its `man` format
    script) and the non-namespaced DocBook XSL stylesheets (whose
    `stripNS` pre-pass doesn't re-apply `strip-space` on the rebuilt
    tree). Neither side ships a fix; the agreed-upon workaround, used by
    other projects (for example Git's documentation build), is to import
    the namespaced manpages stylesheet ourselves and pass this file to
    xmlto with `-x` so that it replaces the default base.
    -->
    <xsl:import href="http://docbook.sourceforge.net/release/xsl-ns/current/manpages/docbook.xsl"/>

    <!-- External links -->
    <xsl:template match="*[local-name() = 'link']">
        <xsl:variable name="href" select="@*[local-name() = 'href']"/>
        <xsl:apply-templates/>
        <xsl:choose>
            <xsl:when test="starts-with($href, 'mailto:')">
                <xsl:text> &lt;</xsl:text>
                <xsl:value-of select="substring-after($href, 'mailto:')"/>
                <xsl:text>&gt;</xsl:text>
            </xsl:when>
            <xsl:when test="$href != ''">
                <xsl:text> (see &lt;</xsl:text>
                <xsl:value-of select="$href"/>
                <xsl:text>&gt;)</xsl:text>
            </xsl:when>
        </xsl:choose>
    </xsl:template>

    <!--
    Render `<xref linkend="ID"/>` as the title of the target section
    wrapped in smart quotes.

    Overrides the DocBook XSL default, which prefixes the title with
    "the section called" that can read awkwardly in our sources.
    -->
    <xsl:template match="*[local-name() = 'xref']" priority="1">
        <xsl:variable name="linkend" select="@linkend"/>
        <xsl:variable name="target" select="(//*[@xml:id = $linkend])[1]"/>
        <xsl:text>\(lq</xsl:text>
        <xsl:apply-templates select="$target/*[local-name() = 'title']/node()"/>
        <xsl:text>\(rq</xsl:text>
    </xsl:template>

    <!-- Literal -->
    <xsl:template match="*[local-name() = 'literal' and local-name(..) != 'title']">
        <xsl:text>\fB</xsl:text>
        <xsl:call-template name="escape-roff-backslash">
            <xsl:with-param name="text" select="."/>
        </xsl:call-template>
        <xsl:text>\fR</xsl:text>
    </xsl:template>

    <!--
    Strong emphasis of the single word "not" or "all": render it
    uppercased and bold.

    Source uses `*not*`/`*all*` so that the AsciiDoc reads naturally;
    the man page shows the conventional emphatic "NOT"/"ALL".
    -->
    <xsl:template match="*[local-name() = 'emphasis'][@role = 'strong'][normalize-space(.) = 'not']">
        <xsl:text>\fBNOT\fR</xsl:text>
    </xsl:template>
    <xsl:template match="*[local-name() = 'emphasis'][@role = 'strong'][normalize-space(.) = 'all']">
        <xsl:text>\fBALL\fR</xsl:text>
    </xsl:template>

    <!--
    Recursively replace each '\' with '\e' so a literal backslash
    survives roff processing intact.
    -->
    <xsl:template name="escape-roff-backslash">
        <xsl:param name="text"/>
        <xsl:choose>
            <xsl:when test="contains($text, '\')">
                <xsl:value-of select="substring-before($text, '\')"/>
                <xsl:text>\e</xsl:text>
                <xsl:call-template name="escape-roff-backslash">
                    <xsl:with-param name="text" select="substring-after($text, '\')"/>
                </xsl:call-template>
            </xsl:when>
            <xsl:otherwise>
                <xsl:value-of select="$text"/>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>

    <!-- Disable end notes -->
    <xsl:param name="man.endnotes.are.numbered">0</xsl:param>
</xsl:stylesheet>

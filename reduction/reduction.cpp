<!DOCTYPE html>
<html lang="en"><head>
<meta http-equiv="content-type" content="text/html; charset=UTF-8"><meta charset="utf-8"><link rel="icon" href="https://leetgpu.com/alphagpu.png"><meta name="viewport" content="width=device-width,initial-scale=1"><meta name="theme-color" content="#000000"><meta name="description" content="LeetGPU - Online CUDA Playground"><link rel="apple-touch-icon" href="https://leetgpu.com/alphagpu.png"><link rel="manifest" href="https://leetgpu.com/manifest.json"><title>LeetGPU</title><style>body,html{background-color:#151515;margin:0;padding:0}</style><script defer="defer" src="reduction_files/main.1ca4a744.js"></script><link href="reduction_files/main.1755fe45.css" rel="stylesheet"><style>/**
 * Copyright (c) 2014 The xterm.js authors. All rights reserved.
 * Copyright (c) 2012-2013, Christopher Jeffrey (MIT License)
 * https://github.com/chjj/term.js
 * @license MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Originally forked from (with the author's permission):
 *   Fabrice Bellard's javascript vt100 for jslinux:
 *   http://bellard.org/jslinux/
 *   Copyright (c) 2011 Fabrice Bellard
 *   The original design remains. The terminal itself
 *   has been extended to include xterm CSI codes, among
 *   other features.
 */

/**
 *  Default styles for xterm.js
 */

.xterm {
    cursor: text;
    position: relative;
    user-select: none;
    -ms-user-select: none;
    -webkit-user-select: none;
}

.xterm.focus,
.xterm:focus {
    outline: none;
}

.xterm .xterm-helpers {
    position: absolute;
    top: 0;
    /**
     * The z-index of the helpers must be higher than the canvases in order for
     * IMEs to appear on top.
     */
    z-index: 5;
}

.xterm .xterm-helper-textarea {
    padding: 0;
    border: 0;
    margin: 0;
    /* Move textarea out of the screen to the far left, so that the cursor is not visible */
    position: absolute;
    opacity: 0;
    left: -9999em;
    top: 0;
    width: 0;
    height: 0;
    z-index: -5;
    /** Prevent wrapping so the IME appears against the textarea at the correct position */
    white-space: nowrap;
    overflow: hidden;
    resize: none;
}

.xterm .composition-view {
    /* TODO: Composition position got messed up somewhere */
    background: #000;
    color: #FFF;
    display: none;
    position: absolute;
    white-space: nowrap;
    z-index: 1;
}

.xterm .composition-view.active {
    display: block;
}

.xterm .xterm-viewport {
    /* On OS X this is required in order for the scroll bar to appear fully opaque */
    background-color: #000;
    overflow-y: scroll;
    cursor: default;
    position: absolute;
    right: 0;
    left: 0;
    top: 0;
    bottom: 0;
}

.xterm .xterm-screen {
    position: relative;
}

.xterm .xterm-screen canvas {
    position: absolute;
    left: 0;
    top: 0;
}

.xterm .xterm-scroll-area {
    visibility: hidden;
}

.xterm-char-measure-element {
    display: inline-block;
    visibility: hidden;
    position: absolute;
    top: 0;
    left: -9999em;
    line-height: normal;
}

.xterm.enable-mouse-events {
    /* When mouse events are enabled (eg. tmux), revert to the standard pointer cursor */
    cursor: default;
}

.xterm.xterm-cursor-pointer,
.xterm .xterm-cursor-pointer {
    cursor: pointer;
}

.xterm.column-select.focus {
    /* Column selection mode */
    cursor: crosshair;
}

.xterm .xterm-accessibility:not(.debug),
.xterm .xterm-message {
    position: absolute;
    left: 0;
    top: 0;
    bottom: 0;
    right: 0;
    z-index: 10;
    color: transparent;
    pointer-events: none;
}

.xterm .xterm-accessibility-tree:not(.debug) *::selection {
  color: transparent;
}

.xterm .xterm-accessibility-tree {
  user-select: text;
  white-space: pre;
}

.xterm .live-region {
    position: absolute;
    left: -9999px;
    width: 1px;
    height: 1px;
    overflow: hidden;
}

.xterm-dim {
    /* Dim should not apply to background, so the opacity of the foreground color is applied
     * explicitly in the generated class and reset to 1 here */
    opacity: 1 !important;
}

.xterm-underline-1 { text-decoration: underline; }
.xterm-underline-2 { text-decoration: double underline; }
.xterm-underline-3 { text-decoration: wavy underline; }
.xterm-underline-4 { text-decoration: dotted underline; }
.xterm-underline-5 { text-decoration: dashed underline; }

.xterm-overline {
    text-decoration: overline;
}

.xterm-overline.xterm-underline-1 { text-decoration: overline underline; }
.xterm-overline.xterm-underline-2 { text-decoration: overline double underline; }
.xterm-overline.xterm-underline-3 { text-decoration: overline wavy underline; }
.xterm-overline.xterm-underline-4 { text-decoration: overline dotted underline; }
.xterm-overline.xterm-underline-5 { text-decoration: overline dashed underline; }

.xterm-strikethrough {
    text-decoration: line-through;
}

.xterm-screen .xterm-decoration-container .xterm-decoration {
	z-index: 6;
	position: absolute;
}

.xterm-screen .xterm-decoration-container .xterm-decoration.xterm-decoration-top-layer {
	z-index: 7;
}

.xterm-decoration-overview-ruler {
    z-index: 8;
    position: absolute;
    top: 0;
    right: 0;
    pointer-events: none;
}

.xterm-decoration-top {
    z-index: 2;
    position: relative;
}
</style><script async="async" type="text/javascript" src="reduction_files/editor.main.js"></script><link rel="stylesheet" type="text/css" data-name="vs/editor/editor.main" href="reduction_files/editor.main.css"><script async="async" type="text/javascript" src="reduction_files/editor.main.nls.js"></script><style type="text/css" media="screen" class="monaco-colors">.codicon-add:before { content: '\ea60'; }
.codicon-plus:before { content: '\ea60'; }
.codicon-gist-new:before { content: '\ea60'; }
.codicon-repo-create:before { content: '\ea60'; }
.codicon-lightbulb:before { content: '\ea61'; }
.codicon-light-bulb:before { content: '\ea61'; }
.codicon-repo:before { content: '\ea62'; }
.codicon-repo-delete:before { content: '\ea62'; }
.codicon-gist-fork:before { content: '\ea63'; }
.codicon-repo-forked:before { content: '\ea63'; }
.codicon-git-pull-request:before { content: '\ea64'; }
.codicon-git-pull-request-abandoned:before { content: '\ea64'; }
.codicon-record-keys:before { content: '\ea65'; }
.codicon-keyboard:before { content: '\ea65'; }
.codicon-tag:before { content: '\ea66'; }
.codicon-tag-add:before { content: '\ea66'; }
.codicon-tag-remove:before { content: '\ea66'; }
.codicon-git-pull-request-label:before { content: '\ea66'; }
.codicon-person:before { content: '\ea67'; }
.codicon-person-follow:before { content: '\ea67'; }
.codicon-person-outline:before { content: '\ea67'; }
.codicon-person-filled:before { content: '\ea67'; }
.codicon-git-branch:before { content: '\ea68'; }
.codicon-git-branch-create:before { content: '\ea68'; }
.codicon-git-branch-delete:before { content: '\ea68'; }
.codicon-source-control:before { content: '\ea68'; }
.codicon-mirror:before { content: '\ea69'; }
.codicon-mirror-public:before { content: '\ea69'; }
.codicon-star:before { content: '\ea6a'; }
.codicon-star-add:before { content: '\ea6a'; }
.codicon-star-delete:before { content: '\ea6a'; }
.codicon-star-empty:before { content: '\ea6a'; }
.codicon-comment:before { content: '\ea6b'; }
.codicon-comment-add:before { content: '\ea6b'; }
.codicon-alert:before { content: '\ea6c'; }
.codicon-warning:before { content: '\ea6c'; }
.codicon-search:before { content: '\ea6d'; }
.codicon-search-save:before { content: '\ea6d'; }
.codicon-log-out:before { content: '\ea6e'; }
.codicon-sign-out:before { content: '\ea6e'; }
.codicon-log-in:before { content: '\ea6f'; }
.codicon-sign-in:before { content: '\ea6f'; }
.codicon-eye:before { content: '\ea70'; }
.codicon-eye-unwatch:before { content: '\ea70'; }
.codicon-eye-watch:before { content: '\ea70'; }
.codicon-circle-filled:before { content: '\ea71'; }
.codicon-primitive-dot:before { content: '\ea71'; }
.codicon-close-dirty:before { content: '\ea71'; }
.codicon-debug-breakpoint:before { content: '\ea71'; }
.codicon-debug-breakpoint-disabled:before { content: '\ea71'; }
.codicon-debug-hint:before { content: '\ea71'; }
.codicon-primitive-square:before { content: '\ea72'; }
.codicon-edit:before { content: '\ea73'; }
.codicon-pencil:before { content: '\ea73'; }
.codicon-info:before { content: '\ea74'; }
.codicon-issue-opened:before { content: '\ea74'; }
.codicon-gist-private:before { content: '\ea75'; }
.codicon-git-fork-private:before { content: '\ea75'; }
.codicon-lock:before { content: '\ea75'; }
.codicon-mirror-private:before { content: '\ea75'; }
.codicon-close:before { content: '\ea76'; }
.codicon-remove-close:before { content: '\ea76'; }
.codicon-x:before { content: '\ea76'; }
.codicon-repo-sync:before { content: '\ea77'; }
.codicon-sync:before { content: '\ea77'; }
.codicon-clone:before { content: '\ea78'; }
.codicon-desktop-download:before { content: '\ea78'; }
.codicon-beaker:before { content: '\ea79'; }
.codicon-microscope:before { content: '\ea79'; }
.codicon-vm:before { content: '\ea7a'; }
.codicon-device-desktop:before { content: '\ea7a'; }
.codicon-file:before { content: '\ea7b'; }
.codicon-file-text:before { content: '\ea7b'; }
.codicon-more:before { content: '\ea7c'; }
.codicon-ellipsis:before { content: '\ea7c'; }
.codicon-kebab-horizontal:before { content: '\ea7c'; }
.codicon-mail-reply:before { content: '\ea7d'; }
.codicon-reply:before { content: '\ea7d'; }
.codicon-organization:before { content: '\ea7e'; }
.codicon-organization-filled:before { content: '\ea7e'; }
.codicon-organization-outline:before { content: '\ea7e'; }
.codicon-new-file:before { content: '\ea7f'; }
.codicon-file-add:before { content: '\ea7f'; }
.codicon-new-folder:before { content: '\ea80'; }
.codicon-file-directory-create:before { content: '\ea80'; }
.codicon-trash:before { content: '\ea81'; }
.codicon-trashcan:before { content: '\ea81'; }
.codicon-history:before { content: '\ea82'; }
.codicon-clock:before { content: '\ea82'; }
.codicon-folder:before { content: '\ea83'; }
.codicon-file-directory:before { content: '\ea83'; }
.codicon-symbol-folder:before { content: '\ea83'; }
.codicon-logo-github:before { content: '\ea84'; }
.codicon-mark-github:before { content: '\ea84'; }
.codicon-github:before { content: '\ea84'; }
.codicon-terminal:before { content: '\ea85'; }
.codicon-console:before { content: '\ea85'; }
.codicon-repl:before { content: '\ea85'; }
.codicon-zap:before { content: '\ea86'; }
.codicon-symbol-event:before { content: '\ea86'; }
.codicon-error:before { content: '\ea87'; }
.codicon-stop:before { content: '\ea87'; }
.codicon-variable:before { content: '\ea88'; }
.codicon-symbol-variable:before { content: '\ea88'; }
.codicon-array:before { content: '\ea8a'; }
.codicon-symbol-array:before { content: '\ea8a'; }
.codicon-symbol-module:before { content: '\ea8b'; }
.codicon-symbol-package:before { content: '\ea8b'; }
.codicon-symbol-namespace:before { content: '\ea8b'; }
.codicon-symbol-object:before { content: '\ea8b'; }
.codicon-symbol-method:before { content: '\ea8c'; }
.codicon-symbol-function:before { content: '\ea8c'; }
.codicon-symbol-constructor:before { content: '\ea8c'; }
.codicon-symbol-boolean:before { content: '\ea8f'; }
.codicon-symbol-null:before { content: '\ea8f'; }
.codicon-symbol-numeric:before { content: '\ea90'; }
.codicon-symbol-number:before { content: '\ea90'; }
.codicon-symbol-structure:before { content: '\ea91'; }
.codicon-symbol-struct:before { content: '\ea91'; }
.codicon-symbol-parameter:before { content: '\ea92'; }
.codicon-symbol-type-parameter:before { content: '\ea92'; }
.codicon-symbol-key:before { content: '\ea93'; }
.codicon-symbol-text:before { content: '\ea93'; }
.codicon-symbol-reference:before { content: '\ea94'; }
.codicon-go-to-file:before { content: '\ea94'; }
.codicon-symbol-enum:before { content: '\ea95'; }
.codicon-symbol-value:before { content: '\ea95'; }
.codicon-symbol-ruler:before { content: '\ea96'; }
.codicon-symbol-unit:before { content: '\ea96'; }
.codicon-activate-breakpoints:before { content: '\ea97'; }
.codicon-archive:before { content: '\ea98'; }
.codicon-arrow-both:before { content: '\ea99'; }
.codicon-arrow-down:before { content: '\ea9a'; }
.codicon-arrow-left:before { content: '\ea9b'; }
.codicon-arrow-right:before { content: '\ea9c'; }
.codicon-arrow-small-down:before { content: '\ea9d'; }
.codicon-arrow-small-left:before { content: '\ea9e'; }
.codicon-arrow-small-right:before { content: '\ea9f'; }
.codicon-arrow-small-up:before { content: '\eaa0'; }
.codicon-arrow-up:before { content: '\eaa1'; }
.codicon-bell:before { content: '\eaa2'; }
.codicon-bold:before { content: '\eaa3'; }
.codicon-book:before { content: '\eaa4'; }
.codicon-bookmark:before { content: '\eaa5'; }
.codicon-debug-breakpoint-conditional-unverified:before { content: '\eaa6'; }
.codicon-debug-breakpoint-conditional:before { content: '\eaa7'; }
.codicon-debug-breakpoint-conditional-disabled:before { content: '\eaa7'; }
.codicon-debug-breakpoint-data-unverified:before { content: '\eaa8'; }
.codicon-debug-breakpoint-data:before { content: '\eaa9'; }
.codicon-debug-breakpoint-data-disabled:before { content: '\eaa9'; }
.codicon-debug-breakpoint-log-unverified:before { content: '\eaaa'; }
.codicon-debug-breakpoint-log:before { content: '\eaab'; }
.codicon-debug-breakpoint-log-disabled:before { content: '\eaab'; }
.codicon-briefcase:before { content: '\eaac'; }
.codicon-broadcast:before { content: '\eaad'; }
.codicon-browser:before { content: '\eaae'; }
.codicon-bug:before { content: '\eaaf'; }
.codicon-calendar:before { content: '\eab0'; }
.codicon-case-sensitive:before { content: '\eab1'; }
.codicon-check:before { content: '\eab2'; }
.codicon-checklist:before { content: '\eab3'; }
.codicon-chevron-down:before { content: '\eab4'; }
.codicon-drop-down-button:before { content: '\eab4'; }
.codicon-chevron-left:before { content: '\eab5'; }
.codicon-chevron-right:before { content: '\eab6'; }
.codicon-chevron-up:before { content: '\eab7'; }
.codicon-chrome-close:before { content: '\eab8'; }
.codicon-chrome-maximize:before { content: '\eab9'; }
.codicon-chrome-minimize:before { content: '\eaba'; }
.codicon-chrome-restore:before { content: '\eabb'; }
.codicon-circle:before { content: '\eabc'; }
.codicon-circle-outline:before { content: '\eabc'; }
.codicon-debug-breakpoint-unverified:before { content: '\eabc'; }
.codicon-circle-slash:before { content: '\eabd'; }
.codicon-circuit-board:before { content: '\eabe'; }
.codicon-clear-all:before { content: '\eabf'; }
.codicon-clippy:before { content: '\eac0'; }
.codicon-close-all:before { content: '\eac1'; }
.codicon-cloud-download:before { content: '\eac2'; }
.codicon-cloud-upload:before { content: '\eac3'; }
.codicon-code:before { content: '\eac4'; }
.codicon-collapse-all:before { content: '\eac5'; }
.codicon-color-mode:before { content: '\eac6'; }
.codicon-comment-discussion:before { content: '\eac7'; }
.codicon-compare-changes:before { content: '\eafd'; }
.codicon-credit-card:before { content: '\eac9'; }
.codicon-dash:before { content: '\eacc'; }
.codicon-dashboard:before { content: '\eacd'; }
.codicon-database:before { content: '\eace'; }
.codicon-debug-continue:before { content: '\eacf'; }
.codicon-debug-disconnect:before { content: '\ead0'; }
.codicon-debug-pause:before { content: '\ead1'; }
.codicon-debug-restart:before { content: '\ead2'; }
.codicon-debug-start:before { content: '\ead3'; }
.codicon-debug-step-into:before { content: '\ead4'; }
.codicon-debug-step-out:before { content: '\ead5'; }
.codicon-debug-step-over:before { content: '\ead6'; }
.codicon-debug-stop:before { content: '\ead7'; }
.codicon-debug:before { content: '\ead8'; }
.codicon-device-camera-video:before { content: '\ead9'; }
.codicon-device-camera:before { content: '\eada'; }
.codicon-device-mobile:before { content: '\eadb'; }
.codicon-diff-added:before { content: '\eadc'; }
.codicon-diff-ignored:before { content: '\eadd'; }
.codicon-diff-modified:before { content: '\eade'; }
.codicon-diff-removed:before { content: '\eadf'; }
.codicon-diff-renamed:before { content: '\eae0'; }
.codicon-diff:before { content: '\eae1'; }
.codicon-discard:before { content: '\eae2'; }
.codicon-editor-layout:before { content: '\eae3'; }
.codicon-empty-window:before { content: '\eae4'; }
.codicon-exclude:before { content: '\eae5'; }
.codicon-extensions:before { content: '\eae6'; }
.codicon-eye-closed:before { content: '\eae7'; }
.codicon-file-binary:before { content: '\eae8'; }
.codicon-file-code:before { content: '\eae9'; }
.codicon-file-media:before { content: '\eaea'; }
.codicon-file-pdf:before { content: '\eaeb'; }
.codicon-file-submodule:before { content: '\eaec'; }
.codicon-file-symlink-directory:before { content: '\eaed'; }
.codicon-file-symlink-file:before { content: '\eaee'; }
.codicon-file-zip:before { content: '\eaef'; }
.codicon-files:before { content: '\eaf0'; }
.codicon-filter:before { content: '\eaf1'; }
.codicon-flame:before { content: '\eaf2'; }
.codicon-fold-down:before { content: '\eaf3'; }
.codicon-fold-up:before { content: '\eaf4'; }
.codicon-fold:before { content: '\eaf5'; }
.codicon-folder-active:before { content: '\eaf6'; }
.codicon-folder-opened:before { content: '\eaf7'; }
.codicon-gear:before { content: '\eaf8'; }
.codicon-gift:before { content: '\eaf9'; }
.codicon-gist-secret:before { content: '\eafa'; }
.codicon-gist:before { content: '\eafb'; }
.codicon-git-commit:before { content: '\eafc'; }
.codicon-git-compare:before { content: '\eafd'; }
.codicon-git-merge:before { content: '\eafe'; }
.codicon-github-action:before { content: '\eaff'; }
.codicon-github-alt:before { content: '\eb00'; }
.codicon-globe:before { content: '\eb01'; }
.codicon-grabber:before { content: '\eb02'; }
.codicon-graph:before { content: '\eb03'; }
.codicon-gripper:before { content: '\eb04'; }
.codicon-heart:before { content: '\eb05'; }
.codicon-home:before { content: '\eb06'; }
.codicon-horizontal-rule:before { content: '\eb07'; }
.codicon-hubot:before { content: '\eb08'; }
.codicon-inbox:before { content: '\eb09'; }
.codicon-issue-closed:before { content: '\eba4'; }
.codicon-issue-reopened:before { content: '\eb0b'; }
.codicon-issues:before { content: '\eb0c'; }
.codicon-italic:before { content: '\eb0d'; }
.codicon-jersey:before { content: '\eb0e'; }
.codicon-json:before { content: '\eb0f'; }
.codicon-bracket:before { content: '\eb0f'; }
.codicon-kebab-vertical:before { content: '\eb10'; }
.codicon-key:before { content: '\eb11'; }
.codicon-law:before { content: '\eb12'; }
.codicon-lightbulb-autofix:before { content: '\eb13'; }
.codicon-link-external:before { content: '\eb14'; }
.codicon-link:before { content: '\eb15'; }
.codicon-list-ordered:before { content: '\eb16'; }
.codicon-list-unordered:before { content: '\eb17'; }
.codicon-live-share:before { content: '\eb18'; }
.codicon-loading:before { content: '\eb19'; }
.codicon-location:before { content: '\eb1a'; }
.codicon-mail-read:before { content: '\eb1b'; }
.codicon-mail:before { content: '\eb1c'; }
.codicon-markdown:before { content: '\eb1d'; }
.codicon-megaphone:before { content: '\eb1e'; }
.codicon-mention:before { content: '\eb1f'; }
.codicon-milestone:before { content: '\eb20'; }
.codicon-git-pull-request-milestone:before { content: '\eb20'; }
.codicon-mortar-board:before { content: '\eb21'; }
.codicon-move:before { content: '\eb22'; }
.codicon-multiple-windows:before { content: '\eb23'; }
.codicon-mute:before { content: '\eb24'; }
.codicon-no-newline:before { content: '\eb25'; }
.codicon-note:before { content: '\eb26'; }
.codicon-octoface:before { content: '\eb27'; }
.codicon-open-preview:before { content: '\eb28'; }
.codicon-package:before { content: '\eb29'; }
.codicon-paintcan:before { content: '\eb2a'; }
.codicon-pin:before { content: '\eb2b'; }
.codicon-play:before { content: '\eb2c'; }
.codicon-run:before { content: '\eb2c'; }
.codicon-plug:before { content: '\eb2d'; }
.codicon-preserve-case:before { content: '\eb2e'; }
.codicon-preview:before { content: '\eb2f'; }
.codicon-project:before { content: '\eb30'; }
.codicon-pulse:before { content: '\eb31'; }
.codicon-question:before { content: '\eb32'; }
.codicon-quote:before { content: '\eb33'; }
.codicon-radio-tower:before { content: '\eb34'; }
.codicon-reactions:before { content: '\eb35'; }
.codicon-references:before { content: '\eb36'; }
.codicon-refresh:before { content: '\eb37'; }
.codicon-regex:before { content: '\eb38'; }
.codicon-remote-explorer:before { content: '\eb39'; }
.codicon-remote:before { content: '\eb3a'; }
.codicon-remove:before { content: '\eb3b'; }
.codicon-replace-all:before { content: '\eb3c'; }
.codicon-replace:before { content: '\eb3d'; }
.codicon-repo-clone:before { content: '\eb3e'; }
.codicon-repo-force-push:before { content: '\eb3f'; }
.codicon-repo-pull:before { content: '\eb40'; }
.codicon-repo-push:before { content: '\eb41'; }
.codicon-report:before { content: '\eb42'; }
.codicon-request-changes:before { content: '\eb43'; }
.codicon-rocket:before { content: '\eb44'; }
.codicon-root-folder-opened:before { content: '\eb45'; }
.codicon-root-folder:before { content: '\eb46'; }
.codicon-rss:before { content: '\eb47'; }
.codicon-ruby:before { content: '\eb48'; }
.codicon-save-all:before { content: '\eb49'; }
.codicon-save-as:before { content: '\eb4a'; }
.codicon-save:before { content: '\eb4b'; }
.codicon-screen-full:before { content: '\eb4c'; }
.codicon-screen-normal:before { content: '\eb4d'; }
.codicon-search-stop:before { content: '\eb4e'; }
.codicon-server:before { content: '\eb50'; }
.codicon-settings-gear:before { content: '\eb51'; }
.codicon-settings:before { content: '\eb52'; }
.codicon-shield:before { content: '\eb53'; }
.codicon-smiley:before { content: '\eb54'; }
.codicon-sort-precedence:before { content: '\eb55'; }
.codicon-split-horizontal:before { content: '\eb56'; }
.codicon-split-vertical:before { content: '\eb57'; }
.codicon-squirrel:before { content: '\eb58'; }
.codicon-star-full:before { content: '\eb59'; }
.codicon-star-half:before { content: '\eb5a'; }
.codicon-symbol-class:before { content: '\eb5b'; }
.codicon-symbol-color:before { content: '\eb5c'; }
.codicon-symbol-customcolor:before { content: '\eb5c'; }
.codicon-symbol-constant:before { content: '\eb5d'; }
.codicon-symbol-enum-member:before { content: '\eb5e'; }
.codicon-symbol-field:before { content: '\eb5f'; }
.codicon-symbol-file:before { content: '\eb60'; }
.codicon-symbol-interface:before { content: '\eb61'; }
.codicon-symbol-keyword:before { content: '\eb62'; }
.codicon-symbol-misc:before { content: '\eb63'; }
.codicon-symbol-operator:before { content: '\eb64'; }
.codicon-symbol-property:before { content: '\eb65'; }
.codicon-wrench:before { content: '\eb65'; }
.codicon-wrench-subaction:before { content: '\eb65'; }
.codicon-symbol-snippet:before { content: '\eb66'; }
.codicon-tasklist:before { content: '\eb67'; }
.codicon-telescope:before { content: '\eb68'; }
.codicon-text-size:before { content: '\eb69'; }
.codicon-three-bars:before { content: '\eb6a'; }
.codicon-thumbsdown:before { content: '\eb6b'; }
.codicon-thumbsup:before { content: '\eb6c'; }
.codicon-tools:before { content: '\eb6d'; }
.codicon-triangle-down:before { content: '\eb6e'; }
.codicon-triangle-left:before { content: '\eb6f'; }
.codicon-triangle-right:before { content: '\eb70'; }
.codicon-triangle-up:before { content: '\eb71'; }
.codicon-twitter:before { content: '\eb72'; }
.codicon-unfold:before { content: '\eb73'; }
.codicon-unlock:before { content: '\eb74'; }
.codicon-unmute:before { content: '\eb75'; }
.codicon-unverified:before { content: '\eb76'; }
.codicon-verified:before { content: '\eb77'; }
.codicon-versions:before { content: '\eb78'; }
.codicon-vm-active:before { content: '\eb79'; }
.codicon-vm-outline:before { content: '\eb7a'; }
.codicon-vm-running:before { content: '\eb7b'; }
.codicon-watch:before { content: '\eb7c'; }
.codicon-whitespace:before { content: '\eb7d'; }
.codicon-whole-word:before { content: '\eb7e'; }
.codicon-window:before { content: '\eb7f'; }
.codicon-word-wrap:before { content: '\eb80'; }
.codicon-zoom-in:before { content: '\eb81'; }
.codicon-zoom-out:before { content: '\eb82'; }
.codicon-list-filter:before { content: '\eb83'; }
.codicon-list-flat:before { content: '\eb84'; }
.codicon-list-selection:before { content: '\eb85'; }
.codicon-selection:before { content: '\eb85'; }
.codicon-list-tree:before { content: '\eb86'; }
.codicon-debug-breakpoint-function-unverified:before { content: '\eb87'; }
.codicon-debug-breakpoint-function:before { content: '\eb88'; }
.codicon-debug-breakpoint-function-disabled:before { content: '\eb88'; }
.codicon-debug-stackframe-active:before { content: '\eb89'; }
.codicon-circle-small-filled:before { content: '\eb8a'; }
.codicon-debug-stackframe-dot:before { content: '\eb8a'; }
.codicon-debug-stackframe:before { content: '\eb8b'; }
.codicon-debug-stackframe-focused:before { content: '\eb8b'; }
.codicon-debug-breakpoint-unsupported:before { content: '\eb8c'; }
.codicon-symbol-string:before { content: '\eb8d'; }
.codicon-debug-reverse-continue:before { content: '\eb8e'; }
.codicon-debug-step-back:before { content: '\eb8f'; }
.codicon-debug-restart-frame:before { content: '\eb90'; }
.codicon-call-incoming:before { content: '\eb92'; }
.codicon-call-outgoing:before { content: '\eb93'; }
.codicon-menu:before { content: '\eb94'; }
.codicon-expand-all:before { content: '\eb95'; }
.codicon-feedback:before { content: '\eb96'; }
.codicon-git-pull-request-reviewer:before { content: '\eb96'; }
.codicon-group-by-ref-type:before { content: '\eb97'; }
.codicon-ungroup-by-ref-type:before { content: '\eb98'; }
.codicon-account:before { content: '\eb99'; }
.codicon-git-pull-request-assignee:before { content: '\eb99'; }
.codicon-bell-dot:before { content: '\eb9a'; }
.codicon-debug-console:before { content: '\eb9b'; }
.codicon-library:before { content: '\eb9c'; }
.codicon-output:before { content: '\eb9d'; }
.codicon-run-all:before { content: '\eb9e'; }
.codicon-sync-ignored:before { content: '\eb9f'; }
.codicon-pinned:before { content: '\eba0'; }
.codicon-github-inverted:before { content: '\eba1'; }
.codicon-debug-alt:before { content: '\eb91'; }
.codicon-server-process:before { content: '\eba2'; }
.codicon-server-environment:before { content: '\eba3'; }
.codicon-pass:before { content: '\eba4'; }
.codicon-stop-circle:before { content: '\eba5'; }
.codicon-play-circle:before { content: '\eba6'; }
.codicon-record:before { content: '\eba7'; }
.codicon-debug-alt-small:before { content: '\eba8'; }
.codicon-vm-connect:before { content: '\eba9'; }
.codicon-cloud:before { content: '\ebaa'; }
.codicon-merge:before { content: '\ebab'; }
.codicon-export:before { content: '\ebac'; }
.codicon-graph-left:before { content: '\ebad'; }
.codicon-magnet:before { content: '\ebae'; }
.codicon-notebook:before { content: '\ebaf'; }
.codicon-redo:before { content: '\ebb0'; }
.codicon-check-all:before { content: '\ebb1'; }
.codicon-pinned-dirty:before { content: '\ebb2'; }
.codicon-pass-filled:before { content: '\ebb3'; }
.codicon-circle-large-filled:before { content: '\ebb4'; }
.codicon-circle-large:before { content: '\ebb5'; }
.codicon-circle-large-outline:before { content: '\ebb5'; }
.codicon-combine:before { content: '\ebb6'; }
.codicon-gather:before { content: '\ebb6'; }
.codicon-table:before { content: '\ebb7'; }
.codicon-variable-group:before { content: '\ebb8'; }
.codicon-type-hierarchy:before { content: '\ebb9'; }
.codicon-type-hierarchy-sub:before { content: '\ebba'; }
.codicon-type-hierarchy-super:before { content: '\ebbb'; }
.codicon-git-pull-request-create:before { content: '\ebbc'; }
.codicon-run-above:before { content: '\ebbd'; }
.codicon-run-below:before { content: '\ebbe'; }
.codicon-notebook-template:before { content: '\ebbf'; }
.codicon-debug-rerun:before { content: '\ebc0'; }
.codicon-workspace-trusted:before { content: '\ebc1'; }
.codicon-workspace-untrusted:before { content: '\ebc2'; }
.codicon-workspace-unspecified:before { content: '\ebc3'; }
.codicon-terminal-cmd:before { content: '\ebc4'; }
.codicon-terminal-debian:before { content: '\ebc5'; }
.codicon-terminal-linux:before { content: '\ebc6'; }
.codicon-terminal-powershell:before { content: '\ebc7'; }
.codicon-terminal-tmux:before { content: '\ebc8'; }
.codicon-terminal-ubuntu:before { content: '\ebc9'; }
.codicon-terminal-bash:before { content: '\ebca'; }
.codicon-arrow-swap:before { content: '\ebcb'; }
.codicon-copy:before { content: '\ebcc'; }
.codicon-person-add:before { content: '\ebcd'; }
.codicon-filter-filled:before { content: '\ebce'; }
.codicon-wand:before { content: '\ebcf'; }
.codicon-debug-line-by-line:before { content: '\ebd0'; }
.codicon-inspect:before { content: '\ebd1'; }
.codicon-layers:before { content: '\ebd2'; }
.codicon-layers-dot:before { content: '\ebd3'; }
.codicon-layers-active:before { content: '\ebd4'; }
.codicon-compass:before { content: '\ebd5'; }
.codicon-compass-dot:before { content: '\ebd6'; }
.codicon-compass-active:before { content: '\ebd7'; }
.codicon-azure:before { content: '\ebd8'; }
.codicon-issue-draft:before { content: '\ebd9'; }
.codicon-git-pull-request-closed:before { content: '\ebda'; }
.codicon-git-pull-request-draft:before { content: '\ebdb'; }
.codicon-debug-all:before { content: '\ebdc'; }
.codicon-debug-coverage:before { content: '\ebdd'; }
.codicon-run-errors:before { content: '\ebde'; }
.codicon-folder-library:before { content: '\ebdf'; }
.codicon-debug-continue-small:before { content: '\ebe0'; }
.codicon-beaker-stop:before { content: '\ebe1'; }
.codicon-graph-line:before { content: '\ebe2'; }
.codicon-graph-scatter:before { content: '\ebe3'; }
.codicon-pie-chart:before { content: '\ebe4'; }
.codicon-bracket-dot:before { content: '\ebe5'; }
.codicon-bracket-error:before { content: '\ebe6'; }
.codicon-lock-small:before { content: '\ebe7'; }
.codicon-azure-devops:before { content: '\ebe8'; }
.codicon-verified-filled:before { content: '\ebe9'; }
.codicon-newline:before { content: '\ebea'; }
.codicon-layout:before { content: '\ebeb'; }
.codicon-layout-activitybar-left:before { content: '\ebec'; }
.codicon-layout-activitybar-right:before { content: '\ebed'; }
.codicon-layout-panel-left:before { content: '\ebee'; }
.codicon-layout-panel-center:before { content: '\ebef'; }
.codicon-layout-panel-justify:before { content: '\ebf0'; }
.codicon-layout-panel-right:before { content: '\ebf1'; }
.codicon-layout-panel:before { content: '\ebf2'; }
.codicon-layout-sidebar-left:before { content: '\ebf3'; }
.codicon-layout-sidebar-right:before { content: '\ebf4'; }
.codicon-layout-statusbar:before { content: '\ebf5'; }
.codicon-layout-menubar:before { content: '\ebf6'; }
.codicon-layout-centered:before { content: '\ebf7'; }
.codicon-layout-sidebar-right-off:before { content: '\ec00'; }
.codicon-layout-panel-off:before { content: '\ec01'; }
.codicon-layout-sidebar-left-off:before { content: '\ec02'; }
.codicon-target:before { content: '\ebf8'; }
.codicon-indent:before { content: '\ebf9'; }
.codicon-record-small:before { content: '\ebfa'; }
.codicon-error-small:before { content: '\ebfb'; }
.codicon-arrow-circle-down:before { content: '\ebfc'; }
.codicon-arrow-circle-left:before { content: '\ebfd'; }
.codicon-arrow-circle-right:before { content: '\ebfe'; }
.codicon-arrow-circle-up:before { content: '\ebff'; }
.codicon-heart-filled:before { content: '\ec04'; }
.codicon-map:before { content: '\ec05'; }
.codicon-map-filled:before { content: '\ec06'; }
.codicon-circle-small:before { content: '\ec07'; }
.codicon-bell-slash:before { content: '\ec08'; }
.codicon-bell-slash-dot:before { content: '\ec09'; }
.codicon-comment-unresolved:before { content: '\ec0a'; }
.codicon-git-pull-request-go-to-changes:before { content: '\ec0b'; }
.codicon-git-pull-request-new-changes:before { content: '\ec0c'; }
.codicon-search-fuzzy:before { content: '\ec0d'; }
.codicon-comment-draft:before { content: '\ec0e'; }
.codicon-send:before { content: '\ec0f'; }
.codicon-sparkle:before { content: '\ec10'; }
.codicon-insert:before { content: '\ec11'; }
.codicon-mic:before { content: '\ec12'; }
.codicon-dialog-error:before { content: '\ea87'; }
.codicon-dialog-warning:before { content: '\ea6c'; }
.codicon-dialog-info:before { content: '\ea74'; }
.codicon-dialog-close:before { content: '\ea76'; }
.codicon-tree-item-expanded:before { content: '\eab4'; }
.codicon-tree-filter-on-type-on:before { content: '\eb83'; }
.codicon-tree-filter-on-type-off:before { content: '\eb85'; }
.codicon-tree-filter-clear:before { content: '\ea76'; }
.codicon-tree-item-loading:before { content: '\eb19'; }
.codicon-menu-selection:before { content: '\eab2'; }
.codicon-menu-submenu:before { content: '\eab6'; }
.codicon-menubar-more:before { content: '\ea7c'; }
.codicon-scrollbar-button-left:before { content: '\eb6f'; }
.codicon-scrollbar-button-right:before { content: '\eb70'; }
.codicon-scrollbar-button-up:before { content: '\eb71'; }
.codicon-scrollbar-button-down:before { content: '\eb6e'; }
.codicon-toolbar-more:before { content: '\ea7c'; }
.codicon-quick-input-back:before { content: '\ea9b'; }
.codicon-widget-close:before { content: '\ea76'; }
.codicon-goto-previous-location:before { content: '\eaa1'; }
.codicon-goto-next-location:before { content: '\ea9a'; }
.codicon-diff-insert:before { content: '\ea60'; }
.codicon-diff-remove:before { content: '\eb3b'; }
.codicon-folding-expanded:before { content: '\eab4'; }
.codicon-folding-collapsed:before { content: '\eab6'; }
.codicon-folding-manual-collapsed:before { content: '\eab6'; }
.codicon-folding-manual-expanded:before { content: '\eab4'; }
.codicon-diff-review-insert:before { content: '\ea60'; }
.codicon-diff-review-remove:before { content: '\eb3b'; }
.codicon-diff-review-close:before { content: '\ea76'; }
.codicon-find-selection:before { content: '\eb85'; }
.codicon-find-collapsed:before { content: '\eab6'; }
.codicon-find-expanded:before { content: '\eab4'; }
.codicon-find-replace:before { content: '\eb3d'; }
.codicon-find-replace-all:before { content: '\eb3c'; }
.codicon-find-previous-match:before { content: '\eaa1'; }
.codicon-find-next-match:before { content: '\ea9a'; }
.codicon-suggest-more-info:before { content: '\eab6'; }
.codicon-parameter-hints-next:before { content: '\eab4'; }
.codicon-parameter-hints-previous:before { content: '\eab7'; }
.codicon-inline-suggestion-hints-next:before { content: '\eab6'; }
.codicon-inline-suggestion-hints-previous:before { content: '\eab5'; }
.codicon-extensions-warning-message:before { content: '\ea6c'; }
.codicon-marker-navigation-next:before { content: '\ea9a'; }
.codicon-marker-navigation-previous:before { content: '\eaa1'; }
.monaco-editor .inputarea.ime-input { background-color: #1e1e1e; }
.monaco-editor .unexpected-closing-bracket { color: rgba(255, 18, 18, 0.8); }
.monaco-editor .bracket-highlighting-0 { color: #ffd700; }
.monaco-editor .bracket-highlighting-1 { color: #da70d6; }
.monaco-editor .bracket-highlighting-2 { color: #179fff; }
.monaco-editor .bracket-highlighting-3 { color: #ffd700; }
.monaco-editor .bracket-highlighting-4 { color: #da70d6; }
.monaco-editor .bracket-highlighting-5 { color: #179fff; }
.monaco-editor .bracket-highlighting-6 { color: #ffd700; }
.monaco-editor .bracket-highlighting-7 { color: #da70d6; }
.monaco-editor .bracket-highlighting-8 { color: #179fff; }
.monaco-editor .bracket-highlighting-9 { color: #ffd700; }
.monaco-editor .bracket-highlighting-10 { color: #da70d6; }
.monaco-editor .bracket-highlighting-11 { color: #179fff; }
.monaco-editor .bracket-highlighting-12 { color: #ffd700; }
.monaco-editor .bracket-highlighting-13 { color: #da70d6; }
.monaco-editor .bracket-highlighting-14 { color: #179fff; }
.monaco-editor .bracket-highlighting-15 { color: #ffd700; }
.monaco-editor .bracket-highlighting-16 { color: #da70d6; }
.monaco-editor .bracket-highlighting-17 { color: #179fff; }
.monaco-editor .bracket-highlighting-18 { color: #ffd700; }
.monaco-editor .bracket-highlighting-19 { color: #da70d6; }
.monaco-editor .bracket-highlighting-20 { color: #179fff; }
.monaco-editor .bracket-highlighting-21 { color: #ffd700; }
.monaco-editor .bracket-highlighting-22 { color: #da70d6; }
.monaco-editor .bracket-highlighting-23 { color: #179fff; }
.monaco-editor .bracket-highlighting-24 { color: #ffd700; }
.monaco-editor .bracket-highlighting-25 { color: #da70d6; }
.monaco-editor .bracket-highlighting-26 { color: #179fff; }
.monaco-editor .bracket-highlighting-27 { color: #ffd700; }
.monaco-editor .bracket-highlighting-28 { color: #da70d6; }
.monaco-editor .bracket-highlighting-29 { color: #179fff; }
.monaco-editor .view-overlays .current-line { border: 2px solid #282828; }
.monaco-editor .margin-view-overlays .current-line-margin { border: 2px solid #282828; }
.monaco-editor .bracket-indent-guide.lvl-0 { --guide-color: rgba(255, 215, 0, 0.3); --guide-color-active: #ffd700; }
.monaco-editor .bracket-indent-guide.lvl-1 { --guide-color: rgba(218, 112, 214, 0.3); --guide-color-active: #da70d6; }
.monaco-editor .bracket-indent-guide.lvl-2 { --guide-color: rgba(23, 159, 255, 0.3); --guide-color-active: #179fff; }
.monaco-editor .bracket-indent-guide.lvl-3 { --guide-color: rgba(255, 215, 0, 0.3); --guide-color-active: #ffd700; }
.monaco-editor .bracket-indent-guide.lvl-4 { --guide-color: rgba(218, 112, 214, 0.3); --guide-color-active: #da70d6; }
.monaco-editor .bracket-indent-guide.lvl-5 { --guide-color: rgba(23, 159, 255, 0.3); --guide-color-active: #179fff; }
.monaco-editor .bracket-indent-guide.lvl-6 { --guide-color: rgba(255, 215, 0, 0.3); --guide-color-active: #ffd700; }
.monaco-editor .bracket-indent-guide.lvl-7 { --guide-color: rgba(218, 112, 214, 0.3); --guide-color-active: #da70d6; }
.monaco-editor .bracket-indent-guide.lvl-8 { --guide-color: rgba(23, 159, 255, 0.3); --guide-color-active: #179fff; }
.monaco-editor .bracket-indent-guide.lvl-9 { --guide-color: rgba(255, 215, 0, 0.3); --guide-color-active: #ffd700; }
.monaco-editor .bracket-indent-guide.lvl-10 { --guide-color: rgba(218, 112, 214, 0.3); --guide-color-active: #da70d6; }
.monaco-editor .bracket-indent-guide.lvl-11 { --guide-color: rgba(23, 159, 255, 0.3); --guide-color-active: #179fff; }
.monaco-editor .bracket-indent-guide.lvl-12 { --guide-color: rgba(255, 215, 0, 0.3); --guide-color-active: #ffd700; }
.monaco-editor .bracket-indent-guide.lvl-13 { --guide-color: rgba(218, 112, 214, 0.3); --guide-color-active: #da70d6; }
.monaco-editor .bracket-indent-guide.lvl-14 { --guide-color: rgba(23, 159, 255, 0.3); --guide-color-active: #179fff; }
.monaco-editor .bracket-indent-guide.lvl-15 { --guide-color: rgba(255, 215, 0, 0.3); --guide-color-active: #ffd700; }
.monaco-editor .bracket-indent-guide.lvl-16 { --guide-color: rgba(218, 112, 214, 0.3); --guide-color-active: #da70d6; }
.monaco-editor .bracket-indent-guide.lvl-17 { --guide-color: rgba(23, 159, 255, 0.3); --guide-color-active: #179fff; }
.monaco-editor .bracket-indent-guide.lvl-18 { --guide-color: rgba(255, 215, 0, 0.3); --guide-color-active: #ffd700; }
.monaco-editor .bracket-indent-guide.lvl-19 { --guide-color: rgba(218, 112, 214, 0.3); --guide-color-active: #da70d6; }
.monaco-editor .bracket-indent-guide.lvl-20 { --guide-color: rgba(23, 159, 255, 0.3); --guide-color-active: #179fff; }
.monaco-editor .bracket-indent-guide.lvl-21 { --guide-color: rgba(255, 215, 0, 0.3); --guide-color-active: #ffd700; }
.monaco-editor .bracket-indent-guide.lvl-22 { --guide-color: rgba(218, 112, 214, 0.3); --guide-color-active: #da70d6; }
.monaco-editor .bracket-indent-guide.lvl-23 { --guide-color: rgba(23, 159, 255, 0.3); --guide-color-active: #179fff; }
.monaco-editor .bracket-indent-guide.lvl-24 { --guide-color: rgba(255, 215, 0, 0.3); --guide-color-active: #ffd700; }
.monaco-editor .bracket-indent-guide.lvl-25 { --guide-color: rgba(218, 112, 214, 0.3); --guide-color-active: #da70d6; }
.monaco-editor .bracket-indent-guide.lvl-26 { --guide-color: rgba(23, 159, 255, 0.3); --guide-color-active: #179fff; }
.monaco-editor .bracket-indent-guide.lvl-27 { --guide-color: rgba(255, 215, 0, 0.3); --guide-color-active: #ffd700; }
.monaco-editor .bracket-indent-guide.lvl-28 { --guide-color: rgba(218, 112, 214, 0.3); --guide-color-active: #da70d6; }
.monaco-editor .bracket-indent-guide.lvl-29 { --guide-color: rgba(23, 159, 255, 0.3); --guide-color-active: #179fff; }
.monaco-editor .vertical { box-shadow: 1px 0 0 0 var(--guide-color) inset; }
.monaco-editor .horizontal-top { border-top: 1px solid var(--guide-color); }
.monaco-editor .horizontal-bottom { border-bottom: 1px solid var(--guide-color); }
.monaco-editor .vertical.indent-active { box-shadow: 1px 0 0 0 var(--guide-color-active) inset; }
.monaco-editor .horizontal-top.indent-active { border-top: 1px solid var(--guide-color-active); }
.monaco-editor .horizontal-bottom.indent-active { border-bottom: 1px solid var(--guide-color-active); }
.monaco-editor .lines-content .core-guide-indent.lvl-0 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-1 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-2 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-3 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-4 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-5 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-6 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-7 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-8 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-9 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-10 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-11 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-12 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-13 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-14 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-15 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-16 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-17 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-18 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-19 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-20 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-21 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-22 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-23 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-24 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-25 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-26 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-27 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-28 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent.lvl-29 { --indent-color: #404040; --indent-color-active: #707070; }
.monaco-editor .lines-content .core-guide-indent { box-shadow: 1px 0 0 0 var(--indent-color) inset; }
.monaco-editor .lines-content .core-guide-indent.indent-active { box-shadow: 1px 0 0 0 var(--indent-color-active) inset; }
.monaco-editor .line-numbers.dimmed-line-number { color: rgba(133, 133, 133, 0.4); }
.monaco-editor .cursors-layer .cursor { background-color: #aeafad; border-color: #aeafad; color: #515052; }
.monaco-editor .squiggly-error { background: url("data:image/svg+xml,%3Csvg%20xmlns%3D'http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg'%20viewBox%3D'0%200%206%203'%20enable-background%3D'new%200%200%206%203'%20height%3D'3'%20width%3D'6'%3E%3Cg%20fill%3D'%23f14c4c'%3E%3Cpolygon%20points%3D'5.5%2C0%202.5%2C3%201.1%2C3%204.1%2C0'%2F%3E%3Cpolygon%20points%3D'4%2C0%206%2C2%206%2C0.6%205.4%2C0'%2F%3E%3Cpolygon%20points%3D'0%2C2%201%2C3%202.4%2C3%200%2C0.6'%2F%3E%3C%2Fg%3E%3C%2Fsvg%3E") repeat-x bottom left; }
.monaco-editor .squiggly-warning { background: url("data:image/svg+xml,%3Csvg%20xmlns%3D'http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg'%20viewBox%3D'0%200%206%203'%20enable-background%3D'new%200%200%206%203'%20height%3D'3'%20width%3D'6'%3E%3Cg%20fill%3D'%23cca700'%3E%3Cpolygon%20points%3D'5.5%2C0%202.5%2C3%201.1%2C3%204.1%2C0'%2F%3E%3Cpolygon%20points%3D'4%2C0%206%2C2%206%2C0.6%205.4%2C0'%2F%3E%3Cpolygon%20points%3D'0%2C2%201%2C3%202.4%2C3%200%2C0.6'%2F%3E%3C%2Fg%3E%3C%2Fsvg%3E") repeat-x bottom left; }
.monaco-editor .squiggly-info { background: url("data:image/svg+xml,%3Csvg%20xmlns%3D'http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg'%20viewBox%3D'0%200%206%203'%20enable-background%3D'new%200%200%206%203'%20height%3D'3'%20width%3D'6'%3E%3Cg%20fill%3D'%233794ff'%3E%3Cpolygon%20points%3D'5.5%2C0%202.5%2C3%201.1%2C3%204.1%2C0'%2F%3E%3Cpolygon%20points%3D'4%2C0%206%2C2%206%2C0.6%205.4%2C0'%2F%3E%3Cpolygon%20points%3D'0%2C2%201%2C3%202.4%2C3%200%2C0.6'%2F%3E%3C%2Fg%3E%3C%2Fsvg%3E") repeat-x bottom left; }
.monaco-editor .squiggly-hint { background: url("data:image/svg+xml,%3Csvg%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%20height%3D%223%22%20width%3D%2212%22%3E%3Cg%20fill%3D%22rgba(238%2C%20238%2C%20238%2C%200.7)%22%3E%3Ccircle%20cx%3D%221%22%20cy%3D%221%22%20r%3D%221%22%2F%3E%3Ccircle%20cx%3D%225%22%20cy%3D%221%22%20r%3D%221%22%2F%3E%3Ccircle%20cx%3D%229%22%20cy%3D%221%22%20r%3D%221%22%2F%3E%3C%2Fg%3E%3C%2Fsvg%3E") no-repeat bottom left; }
.monaco-editor.showUnused .squiggly-inline-unnecessary { opacity: 0.667; }

	.monaco-editor .diagonal-fill {
		background-image: linear-gradient(
			-45deg,
			rgba(204, 204, 204, 0.2) 12.5%,
			#0000 12.5%, #0000 50%,
			rgba(204, 204, 204, 0.2) 50%, rgba(204, 204, 204, 0.2) 62.5%,
			#0000 62.5%, #0000 100%
		);
		background-size: 8px 8px;
	}
	
.monaco-editor .findMatch { background-color: rgba(234, 92, 0, 0.33); }
.monaco-editor .currentFindMatch { background-color: #515c6a; }
.monaco-editor .findScope { background-color: rgba(58, 61, 65, 0.4); }
.monaco-editor .find-widget { background-color: #252526; }
.monaco-editor .find-widget { box-shadow: 0 0 8px 2px rgba(0, 0, 0, 0.36); }
.monaco-editor .find-widget { color: #cccccc; }
.monaco-editor .find-widget.no-results .matchesCount { color: #f48771; }
.monaco-editor .find-widget .monaco-sash { background-color: #454545; }

		.monaco-editor .find-widget .button:not(.disabled):hover,
		.monaco-editor .find-widget .codicon-find-selection:hover {
			background-color: rgba(90, 93, 94, 0.31) !important;
		}
	
.monaco-editor .find-widget .monaco-inputbox.synthetic-focus { outline-color: #007fd4; }
.monaco-editor .selectionHighlight { background-color: rgba(173, 214, 255, 0.07); }
.monaco-editor .monaco-hover .hover-row:not(:first-child):not(:empty) { border-top: 1px solid rgba(69, 69, 69, 0.5); }
.monaco-editor .monaco-hover hr { border-top: 1px solid rgba(69, 69, 69, 0.5); }
.monaco-editor .monaco-hover hr { border-bottom: 0px solid rgba(69, 69, 69, 0.5); }
.monaco-editor, .monaco-diff-editor { --vscode-foreground: #cccccc;
--vscode-disabledForeground: rgba(204, 204, 204, 0.5);
--vscode-errorForeground: #f48771;
--vscode-descriptionForeground: rgba(204, 204, 204, 0.7);
--vscode-icon-foreground: #c5c5c5;
--vscode-focusBorder: #007fd4;
--vscode-textSeparator-foreground: rgba(255, 255, 255, 0.18);
--vscode-textLink-foreground: #3794ff;
--vscode-textLink-activeForeground: #3794ff;
--vscode-textPreformat-foreground: #d7ba7d;
--vscode-textBlockQuote-background: rgba(127, 127, 127, 0.1);
--vscode-textBlockQuote-border: rgba(0, 122, 204, 0.5);
--vscode-textCodeBlock-background: rgba(10, 10, 10, 0.4);
--vscode-widget-shadow: rgba(0, 0, 0, 0.36);
--vscode-input-background: #3c3c3c;
--vscode-input-foreground: #cccccc;
--vscode-inputOption-activeBorder: #007acc;
--vscode-inputOption-hoverBackground: rgba(90, 93, 94, 0.5);
--vscode-inputOption-activeBackground: rgba(0, 127, 212, 0.4);
--vscode-inputOption-activeForeground: #ffffff;
--vscode-input-placeholderForeground: rgba(204, 204, 204, 0.5);
--vscode-inputValidation-infoBackground: #063b49;
--vscode-inputValidation-infoBorder: #007acc;
--vscode-inputValidation-warningBackground: #352a05;
--vscode-inputValidation-warningBorder: #b89500;
--vscode-inputValidation-errorBackground: #5a1d1d;
--vscode-inputValidation-errorBorder: #be1100;
--vscode-dropdown-background: #3c3c3c;
--vscode-dropdown-foreground: #f0f0f0;
--vscode-dropdown-border: #3c3c3c;
--vscode-button-foreground: #ffffff;
--vscode-button-separator: rgba(255, 255, 255, 0.4);
--vscode-button-background: #0e639c;
--vscode-button-hoverBackground: #1177bb;
--vscode-button-secondaryForeground: #ffffff;
--vscode-button-secondaryBackground: #3a3d41;
--vscode-button-secondaryHoverBackground: #45494e;
--vscode-badge-background: #4d4d4d;
--vscode-badge-foreground: #ffffff;
--vscode-scrollbar-shadow: #000000;
--vscode-scrollbarSlider-background: rgba(121, 121, 121, 0.4);
--vscode-scrollbarSlider-hoverBackground: rgba(100, 100, 100, 0.7);
--vscode-scrollbarSlider-activeBackground: rgba(191, 191, 191, 0.4);
--vscode-progressBar-background: #0e70c0;
--vscode-editorError-foreground: #f14c4c;
--vscode-editorWarning-foreground: #cca700;
--vscode-editorInfo-foreground: #3794ff;
--vscode-editorHint-foreground: rgba(238, 238, 238, 0.7);
--vscode-sash-hoverBorder: #007fd4;
--vscode-editor-background: #1e1e1e;
--vscode-editor-foreground: #d4d4d4;
--vscode-editorStickyScroll-background: #1e1e1e;
--vscode-editorStickyScrollHover-background: #2a2d2e;
--vscode-editorWidget-background: #252526;
--vscode-editorWidget-foreground: #cccccc;
--vscode-editorWidget-border: #454545;
--vscode-quickInput-background: #252526;
--vscode-quickInput-foreground: #cccccc;
--vscode-quickInputTitle-background: rgba(255, 255, 255, 0.1);
--vscode-pickerGroup-foreground: #3794ff;
--vscode-pickerGroup-border: #3f3f46;
--vscode-keybindingLabel-background: rgba(128, 128, 128, 0.17);
--vscode-keybindingLabel-foreground: #cccccc;
--vscode-keybindingLabel-border: rgba(51, 51, 51, 0.6);
--vscode-keybindingLabel-bottomBorder: rgba(68, 68, 68, 0.6);
--vscode-editor-selectionBackground: #264f78;
--vscode-editor-inactiveSelectionBackground: #3a3d41;
--vscode-editor-selectionHighlightBackground: rgba(173, 214, 255, 0.15);
--vscode-editor-findMatchBackground: #515c6a;
--vscode-editor-findMatchHighlightBackground: rgba(234, 92, 0, 0.33);
--vscode-editor-findRangeHighlightBackground: rgba(58, 61, 65, 0.4);
--vscode-searchEditor-findMatchBackground: rgba(234, 92, 0, 0.22);
--vscode-search-resultsInfoForeground: rgba(204, 204, 204, 0.65);
--vscode-editor-hoverHighlightBackground: rgba(38, 79, 120, 0.25);
--vscode-editorHoverWidget-background: #252526;
--vscode-editorHoverWidget-foreground: #cccccc;
--vscode-editorHoverWidget-border: #454545;
--vscode-editorHoverWidget-statusBarBackground: #2c2c2d;
--vscode-editorLink-activeForeground: #4e94ce;
--vscode-editorInlayHint-foreground: #969696;
--vscode-editorInlayHint-background: rgba(77, 77, 77, 0.1);
--vscode-editorInlayHint-typeForeground: #969696;
--vscode-editorInlayHint-typeBackground: rgba(77, 77, 77, 0.1);
--vscode-editorInlayHint-parameterForeground: #969696;
--vscode-editorInlayHint-parameterBackground: rgba(77, 77, 77, 0.1);
--vscode-editorLightBulb-foreground: #ffcc00;
--vscode-editorLightBulbAutoFix-foreground: #75beff;
--vscode-diffEditor-insertedTextBackground: rgba(156, 204, 44, 0.2);
--vscode-diffEditor-removedTextBackground: rgba(255, 0, 0, 0.2);
--vscode-diffEditor-insertedLineBackground: rgba(155, 185, 85, 0.2);
--vscode-diffEditor-removedLineBackground: rgba(255, 0, 0, 0.2);
--vscode-diffEditor-diagonalFill: rgba(204, 204, 204, 0.2);
--vscode-diffEditor-unchangedRegionBackground: #3e3e3e;
--vscode-diffEditor-unchangedRegionForeground: #a3a2a2;
--vscode-diffEditor-unchangedCodeBackground: rgba(116, 116, 116, 0.16);
--vscode-list-focusOutline: #007fd4;
--vscode-list-activeSelectionBackground: #04395e;
--vscode-list-activeSelectionForeground: #ffffff;
--vscode-list-inactiveSelectionBackground: #37373d;
--vscode-list-hoverBackground: #2a2d2e;
--vscode-list-dropBackground: #062f4a;
--vscode-list-highlightForeground: #2aaaff;
--vscode-list-focusHighlightForeground: #2aaaff;
--vscode-list-invalidItemForeground: #b89500;
--vscode-list-errorForeground: #f88070;
--vscode-list-warningForeground: #cca700;
--vscode-listFilterWidget-background: #252526;
--vscode-listFilterWidget-outline: rgba(0, 0, 0, 0);
--vscode-listFilterWidget-noMatchesOutline: #be1100;
--vscode-listFilterWidget-shadow: rgba(0, 0, 0, 0.36);
--vscode-list-filterMatchBackground: rgba(234, 92, 0, 0.33);
--vscode-tree-indentGuidesStroke: #585858;
--vscode-tree-inactiveIndentGuidesStroke: rgba(88, 88, 88, 0.4);
--vscode-tree-tableColumnsBorder: rgba(204, 204, 204, 0.13);
--vscode-tree-tableOddRowsBackground: rgba(204, 204, 204, 0.04);
--vscode-list-deemphasizedForeground: #8c8c8c;
--vscode-checkbox-background: #3c3c3c;
--vscode-checkbox-selectBackground: #252526;
--vscode-checkbox-foreground: #f0f0f0;
--vscode-checkbox-border: #3c3c3c;
--vscode-checkbox-selectBorder: #c5c5c5;
--vscode-quickInputList-focusForeground: #ffffff;
--vscode-quickInputList-focusBackground: #04395e;
--vscode-menu-foreground: #f0f0f0;
--vscode-menu-background: #3c3c3c;
--vscode-menu-selectionForeground: #ffffff;
--vscode-menu-selectionBackground: #04395e;
--vscode-menu-separatorBackground: #606060;
--vscode-toolbar-hoverBackground: rgba(90, 93, 94, 0.31);
--vscode-toolbar-activeBackground: rgba(99, 102, 103, 0.31);
--vscode-editor-snippetTabstopHighlightBackground: rgba(124, 124, 124, 0.3);
--vscode-editor-snippetFinalTabstopHighlightBorder: #525252;
--vscode-breadcrumb-foreground: rgba(204, 204, 204, 0.8);
--vscode-breadcrumb-background: #1e1e1e;
--vscode-breadcrumb-focusForeground: #e0e0e0;
--vscode-breadcrumb-activeSelectionForeground: #e0e0e0;
--vscode-breadcrumbPicker-background: #252526;
--vscode-merge-currentHeaderBackground: rgba(64, 200, 174, 0.5);
--vscode-merge-currentContentBackground: rgba(64, 200, 174, 0.2);
--vscode-merge-incomingHeaderBackground: rgba(64, 166, 255, 0.5);
--vscode-merge-incomingContentBackground: rgba(64, 166, 255, 0.2);
--vscode-merge-commonHeaderBackground: rgba(96, 96, 96, 0.4);
--vscode-merge-commonContentBackground: rgba(96, 96, 96, 0.16);
--vscode-editorOverviewRuler-currentContentForeground: rgba(64, 200, 174, 0.5);
--vscode-editorOverviewRuler-incomingContentForeground: rgba(64, 166, 255, 0.5);
--vscode-editorOverviewRuler-commonContentForeground: rgba(96, 96, 96, 0.4);
--vscode-editorOverviewRuler-findMatchForeground: rgba(209, 134, 22, 0.49);
--vscode-editorOverviewRuler-selectionHighlightForeground: rgba(160, 160, 160, 0.8);
--vscode-minimap-findMatchHighlight: #d18616;
--vscode-minimap-selectionOccurrenceHighlight: #676767;
--vscode-minimap-selectionHighlight: #264f78;
--vscode-minimap-errorHighlight: rgba(255, 18, 18, 0.7);
--vscode-minimap-warningHighlight: #cca700;
--vscode-minimap-foregroundOpacity: #000000;
--vscode-minimapSlider-background: rgba(121, 121, 121, 0.2);
--vscode-minimapSlider-hoverBackground: rgba(100, 100, 100, 0.35);
--vscode-minimapSlider-activeBackground: rgba(191, 191, 191, 0.2);
--vscode-problemsErrorIcon-foreground: #f14c4c;
--vscode-problemsWarningIcon-foreground: #cca700;
--vscode-problemsInfoIcon-foreground: #3794ff;
--vscode-charts-foreground: #cccccc;
--vscode-charts-lines: rgba(204, 204, 204, 0.5);
--vscode-charts-red: #f14c4c;
--vscode-charts-blue: #3794ff;
--vscode-charts-yellow: #cca700;
--vscode-charts-orange: #d18616;
--vscode-charts-green: #89d185;
--vscode-charts-purple: #b180d7;
--vscode-diffEditor-move-border: rgba(139, 139, 139, 0.61);
--vscode-diffEditor-moveActive-border: #ffa500;
--vscode-editor-lineHighlightBorder: #282828;
--vscode-editor-rangeHighlightBackground: rgba(255, 255, 255, 0.04);
--vscode-editor-symbolHighlightBackground: rgba(234, 92, 0, 0.33);
--vscode-editorCursor-foreground: #aeafad;
--vscode-editorWhitespace-foreground: rgba(227, 228, 226, 0.16);
--vscode-editorLineNumber-foreground: #858585;
--vscode-editorIndentGuide-background: rgba(227, 228, 226, 0.16);
--vscode-editorIndentGuide-activeBackground: rgba(227, 228, 226, 0.16);
--vscode-editorIndentGuide-background1: #404040;
--vscode-editorIndentGuide-background2: rgba(0, 0, 0, 0);
--vscode-editorIndentGuide-background3: rgba(0, 0, 0, 0);
--vscode-editorIndentGuide-background4: rgba(0, 0, 0, 0);
--vscode-editorIndentGuide-background5: rgba(0, 0, 0, 0);
--vscode-editorIndentGuide-background6: rgba(0, 0, 0, 0);
--vscode-editorIndentGuide-activeBackground1: #707070;
--vscode-editorIndentGuide-activeBackground2: rgba(0, 0, 0, 0);
--vscode-editorIndentGuide-activeBackground3: rgba(0, 0, 0, 0);
--vscode-editorIndentGuide-activeBackground4: rgba(0, 0, 0, 0);
--vscode-editorIndentGuide-activeBackground5: rgba(0, 0, 0, 0);
--vscode-editorIndentGuide-activeBackground6: rgba(0, 0, 0, 0);
--vscode-editorActiveLineNumber-foreground: #c6c6c6;
--vscode-editorLineNumber-activeForeground: #c6c6c6;
--vscode-editorRuler-foreground: #5a5a5a;
--vscode-editorCodeLens-foreground: #999999;
--vscode-editorBracketMatch-background: rgba(0, 100, 0, 0.1);
--vscode-editorBracketMatch-border: #888888;
--vscode-editorOverviewRuler-border: rgba(127, 127, 127, 0.3);
--vscode-editorGutter-background: #1e1e1e;
--vscode-editorUnnecessaryCode-opacity: rgba(0, 0, 0, 0.67);
--vscode-editorGhostText-foreground: rgba(255, 255, 255, 0.34);
--vscode-editorOverviewRuler-rangeHighlightForeground: rgba(0, 122, 204, 0.6);
--vscode-editorOverviewRuler-errorForeground: rgba(255, 18, 18, 0.7);
--vscode-editorOverviewRuler-warningForeground: #cca700;
--vscode-editorOverviewRuler-infoForeground: #3794ff;
--vscode-editorBracketHighlight-foreground1: #ffd700;
--vscode-editorBracketHighlight-foreground2: #da70d6;
--vscode-editorBracketHighlight-foreground3: #179fff;
--vscode-editorBracketHighlight-foreground4: rgba(0, 0, 0, 0);
--vscode-editorBracketHighlight-foreground5: rgba(0, 0, 0, 0);
--vscode-editorBracketHighlight-foreground6: rgba(0, 0, 0, 0);
--vscode-editorBracketHighlight-unexpectedBracket-foreground: rgba(255, 18, 18, 0.8);
--vscode-editorBracketPairGuide-background1: rgba(0, 0, 0, 0);
--vscode-editorBracketPairGuide-background2: rgba(0, 0, 0, 0);
--vscode-editorBracketPairGuide-background3: rgba(0, 0, 0, 0);
--vscode-editorBracketPairGuide-background4: rgba(0, 0, 0, 0);
--vscode-editorBracketPairGuide-background5: rgba(0, 0, 0, 0);
--vscode-editorBracketPairGuide-background6: rgba(0, 0, 0, 0);
--vscode-editorBracketPairGuide-activeBackground1: rgba(0, 0, 0, 0);
--vscode-editorBracketPairGuide-activeBackground2: rgba(0, 0, 0, 0);
--vscode-editorBracketPairGuide-activeBackground3: rgba(0, 0, 0, 0);
--vscode-editorBracketPairGuide-activeBackground4: rgba(0, 0, 0, 0);
--vscode-editorBracketPairGuide-activeBackground5: rgba(0, 0, 0, 0);
--vscode-editorBracketPairGuide-activeBackground6: rgba(0, 0, 0, 0);
--vscode-editorUnicodeHighlight-border: #bd9b03;
--vscode-editorUnicodeHighlight-background: rgba(189, 155, 3, 0.15);
--vscode-editor-foldBackground: rgba(38, 79, 120, 0.3);
--vscode-editorGutter-foldingControlForeground: #c5c5c5;
--vscode-editorOverviewRuler-bracketMatchForeground: #a0a0a0;
--vscode-editor-linkedEditingBackground: rgba(255, 0, 0, 0.3);
--vscode-editorHoverWidget-highlightForeground: #2aaaff;
--vscode-symbolIcon-arrayForeground: #cccccc;
--vscode-symbolIcon-booleanForeground: #cccccc;
--vscode-symbolIcon-classForeground: #ee9d28;
--vscode-symbolIcon-colorForeground: #cccccc;
--vscode-symbolIcon-constantForeground: #cccccc;
--vscode-symbolIcon-constructorForeground: #b180d7;
--vscode-symbolIcon-enumeratorForeground: #ee9d28;
--vscode-symbolIcon-enumeratorMemberForeground: #75beff;
--vscode-symbolIcon-eventForeground: #ee9d28;
--vscode-symbolIcon-fieldForeground: #75beff;
--vscode-symbolIcon-fileForeground: #cccccc;
--vscode-symbolIcon-folderForeground: #cccccc;
--vscode-symbolIcon-functionForeground: #b180d7;
--vscode-symbolIcon-interfaceForeground: #75beff;
--vscode-symbolIcon-keyForeground: #cccccc;
--vscode-symbolIcon-keywordForeground: #cccccc;
--vscode-symbolIcon-methodForeground: #b180d7;
--vscode-symbolIcon-moduleForeground: #cccccc;
--vscode-symbolIcon-namespaceForeground: #cccccc;
--vscode-symbolIcon-nullForeground: #cccccc;
--vscode-symbolIcon-numberForeground: #cccccc;
--vscode-symbolIcon-objectForeground: #cccccc;
--vscode-symbolIcon-operatorForeground: #cccccc;
--vscode-symbolIcon-packageForeground: #cccccc;
--vscode-symbolIcon-propertyForeground: #cccccc;
--vscode-symbolIcon-referenceForeground: #cccccc;
--vscode-symbolIcon-snippetForeground: #cccccc;
--vscode-symbolIcon-stringForeground: #cccccc;
--vscode-symbolIcon-structForeground: #cccccc;
--vscode-symbolIcon-textForeground: #cccccc;
--vscode-symbolIcon-typeParameterForeground: #cccccc;
--vscode-symbolIcon-unitForeground: #cccccc;
--vscode-symbolIcon-variableForeground: #75beff;
--vscode-editor-wordHighlightBackground: rgba(87, 87, 87, 0.72);
--vscode-editor-wordHighlightStrongBackground: rgba(0, 73, 114, 0.72);
--vscode-editor-wordHighlightTextBackground: rgba(87, 87, 87, 0.72);
--vscode-editorOverviewRuler-wordHighlightForeground: rgba(160, 160, 160, 0.8);
--vscode-editorOverviewRuler-wordHighlightStrongForeground: rgba(192, 160, 192, 0.8);
--vscode-editorOverviewRuler-wordHighlightTextForeground: rgba(160, 160, 160, 0.8);
--vscode-actionBar-toggledBackground: rgba(0, 127, 212, 0.4);
--vscode-editorSuggestWidget-background: #252526;
--vscode-editorSuggestWidget-border: #454545;
--vscode-editorSuggestWidget-foreground: #d4d4d4;
--vscode-editorSuggestWidget-selectedForeground: #ffffff;
--vscode-editorSuggestWidget-selectedBackground: #04395e;
--vscode-editorSuggestWidget-highlightForeground: #2aaaff;
--vscode-editorSuggestWidget-focusHighlightForeground: #2aaaff;
--vscode-editorSuggestWidgetStatus-foreground: rgba(212, 212, 212, 0.5);
--vscode-peekViewTitle-background: #252526;
--vscode-peekViewTitleLabel-foreground: #ffffff;
--vscode-peekViewTitleDescription-foreground: rgba(204, 204, 204, 0.7);
--vscode-peekView-border: #3794ff;
--vscode-peekViewResult-background: #252526;
--vscode-peekViewResult-lineForeground: #bbbbbb;
--vscode-peekViewResult-fileForeground: #ffffff;
--vscode-peekViewResult-selectionBackground: rgba(51, 153, 255, 0.2);
--vscode-peekViewResult-selectionForeground: #ffffff;
--vscode-peekViewEditor-background: #001f33;
--vscode-peekViewEditorGutter-background: #001f33;
--vscode-peekViewEditorStickyScroll-background: #001f33;
--vscode-peekViewResult-matchHighlightBackground: rgba(234, 92, 0, 0.3);
--vscode-peekViewEditor-matchHighlightBackground: rgba(255, 143, 0, 0.6);
--vscode-editorMarkerNavigationError-background: #f14c4c;
--vscode-editorMarkerNavigationError-headerBackground: rgba(241, 76, 76, 0.1);
--vscode-editorMarkerNavigationWarning-background: #cca700;
--vscode-editorMarkerNavigationWarning-headerBackground: rgba(204, 167, 0, 0.1);
--vscode-editorMarkerNavigationInfo-background: #3794ff;
--vscode-editorMarkerNavigationInfo-headerBackground: rgba(55, 148, 255, 0.1);
--vscode-editorMarkerNavigation-background: #1e1e1e; }

.mtk1 { color: #d4d4d4; }
.mtk2 { color: #1e1e1e; }
.mtk3 { color: #cc6666; }
.mtk4 { color: #9cdcfe; }
.mtk5 { color: #ce9178; }
.mtk6 { color: #b5cea8; }
.mtk7 { color: #608b4e; }
.mtk8 { color: #569cd6; }
.mtk9 { color: #dcdcdc; }
.mtk10 { color: #808080; }
.mtk11 { color: #dcdcaa; }
.mtk12 { color: #f44747; }
.mtk13 { color: #c586c0; }
.mtk14 { color: #a79873; }
.mtk15 { color: #dd6a6f; }
.mtk16 { color: #5bb498; }
.mtk17 { color: #909090; }
.mtk18 { color: #778899; }
.mtk19 { color: #ff00ff; }
.mtk20 { color: #b46695; }
.mtk21 { color: #ff0000; }
.mtk22 { color: #4f76ac; }
.mtk23 { color: #3dc9b0; }
.mtk24 { color: #74b0df; }
.mtk25 { color: #4864aa; }
.mtki { font-style: italic; }
.mtkb { font-weight: bold; }
.mtku { text-decoration: underline; text-underline-position: under; }
.mtks { text-decoration: line-through; }
.mtks.mtku { text-decoration: underline line-through; text-underline-position: under; }</style></head><body style=""><noscript>You need to enable JavaScript to run this app.</noscript><div id="root"><div class="theme-dark"><div class="flex flex-col h-screen bg-[#151515] text-white"><div class="flex items-center p-4 bg-[#151515] border-gray-700 relative"><div class="flex items-center w-full"><a class="text-3xl font-bold tracking-tight bg-gradient-to-r from-[#3ce8e2] via-[#00b3b3] to-[#3ce8e2] bg-clip-text text-transparent" href="https://leetgpu.com/">LeetGPU</a><div class="w-full flex justify-center"><div class="flex items-center space-x-6"><div class="relative"><button class="
          min-w-[200px] max-w-fit px-6 py-1.5
          bg-[#212121] text-gray-100
          rounded-md
          shadow-sm 
          focus:outline-none focus:ring-2 focus:ring-blue-500
          disabled:opacity-50 disabled:cursor-not-allowed
          font-mono text-sm
          flex items-center justify-between
          transition-all duration-200
          cursor-pointer
        "><span>NVIDIA GTX TITAN X</span><svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" aria-hidden="true" data-slot="icon" class="h-4 w-4 ml-2"><path stroke-linecap="round" stroke-linejoin="round" d="m19.5 8.25-7.5 7.5-7.5-7.5"></path></svg></button></div><div class="relative inline-flex"><div class="inline-flex"><button class="
    inline-flex items-center gap-2
    text-sm font-medium
    transition-all duration-200 ease-in-out
    font-mono
    bg-blue-600 text-white hover:bg-blue-700 active:bg-blue-800
    focus:outline-none border-blue-700
   px-4 py-1.5 rounded-l-md border-r flex items-center"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="currentColor" aria-hidden="true" data-slot="icon" class="h-4 w-4 mr-2"><path fill-rule="evenodd" d="M4.5 5.653c0-1.427 1.529-2.33 2.779-1.643l11.54 6.347c1.295.712 1.295 2.573 0 3.286L7.28 19.99c-1.25.687-2.779-.217-2.779-1.643V5.653Z" clip-rule="evenodd"></path></svg>Run</button><button class="
    inline-flex items-center gap-2
    text-sm font-medium
    transition-all duration-200 ease-in-out
    font-mono
    bg-blue-600 text-white hover:bg-blue-700 active:bg-blue-800
    focus:outline-none border-blue-700
   px-2 py-1.5 rounded-r-md border-l focus:ring-0 focus:ring-offset-0 hover:bg-blue-700 active:bg-blue-800"><svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" aria-hidden="true" data-slot="icon" class="h-4 w-4"><path stroke-linecap="round" stroke-linejoin="round" d="m19.5 8.25-7.5 7.5-7.5-7.5"></path></svg></button></div></div><button class="
        inline-flex items-center gap-2
        px-4 py-1.5 rounded-md
        text-sm font-medium
        transition-all duration-200 ease-in-out
        font-mono
        bg-gray-200 text-gray-500 cursor-not-allowed
        focus:outline-none
      " disabled="disabled"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="currentColor" aria-hidden="true" data-slot="icon" class="h-4 w-4 mr-2"><path fill-rule="evenodd" d="M4.5 7.5a3 3 0 0 1 3-3h9a3 3 0 0 1 3 3v9a3 3 0 0 1-3 3h-9a3 3 0 0 1-3-3v-9Z" clip-rule="evenodd"></path></svg>Stop</button><div class="relative"><button class="
          inline-flex items-center gap-2
          px-4 py-1.5 rounded-md
          text-sm font-medium
          transition-all duration-200 ease-in-out
          font-mono
          bg-blue-600 text-white hover:bg-blue-700 active:bg-blue-800
          focus:outline-none
        "><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="currentColor" aria-hidden="true" data-slot="icon" class="h-4 w-4 mr-2"><path fill-rule="evenodd" d="M15.75 4.5a3 3 0 1 1 .825 2.066l-8.421 4.679a3.002 3.002 0 0 1 0 1.51l8.421 4.679a3 3 0 1 1-.729 1.31l-8.421-4.678a3 3 0 1 1 0-4.132l8.421-4.679a3 3 0 0 1-.096-.755Z" clip-rule="evenodd"></path></svg>Share</button></div></div></div><div class="absolute right-4 top-1/2 -translate-y-1/2 flex items-center gap-3"><button class="
        p-1.5 rounded-md transition-colors duration-200
        text-gray-600 hover:bg-gray-800
      " title="Join our Discord"><svg width="23" height="23" viewBox="0 1 71 55" fill="currentColor" xmlns="http://www.w3.org/2000/svg"><path d="M60.1045 4.8978C55.5792 2.8214 50.7265 1.2916 45.6527 0.41542C45.5603 0.39851 45.468 0.440769 45.4204 0.525289C44.7963 1.6353 44.105 3.0834 43.6209 4.2216C38.1637 3.4046 32.7345 3.4046 27.3892 4.2216C26.905 3.0581 26.1886 1.6353 25.5617 0.525289C25.5141 0.443589 25.4218 0.40133 25.3294 0.41542C20.2584 1.2888 15.4057 2.8186 10.8776 4.8978C10.8384 4.9147 10.8048 4.9429 10.7825 4.9795C1.57795 18.7309 -0.943561 32.1443 0.293408 45.3914C0.299005 45.4562 0.335386 45.5182 0.385761 45.5576C6.45866 50.0174 12.3413 52.7249 18.1147 54.5195C18.2071 54.5477 18.305 54.5139 18.3638 54.4378C19.7295 52.5728 20.9469 50.6063 21.9907 48.5383C22.0523 48.4172 21.9935 48.2735 21.8676 48.2256C19.9366 47.4931 18.0979 46.6 16.3292 45.5858C16.1893 45.5041 16.1781 45.304 16.3068 45.2082C16.679 44.9293 17.0513 44.6391 17.4067 44.3461C17.471 44.2926 17.5606 44.2813 17.6362 44.3151C29.2558 49.6202 41.8354 49.6202 53.3179 44.3151C53.3935 44.2785 53.4831 44.2898 53.5502 44.3433C53.9057 44.6363 54.2779 44.9293 54.6529 45.2082C54.7816 45.304 54.7732 45.5041 54.6333 45.5858C52.8646 46.6197 51.0259 47.4931 49.0921 48.2228C48.9662 48.2707 48.9102 48.4172 48.9718 48.5383C50.038 50.6034 51.2554 52.5699 52.5959 54.435C52.6519 54.5139 52.7526 54.5477 52.845 54.5195C58.6464 52.7249 64.529 50.0174 70.6019 45.5576C70.6551 45.5182 70.6887 45.459 70.6943 45.3942C72.1747 30.0791 68.2147 16.7757 60.1968 4.9823C60.1772 4.9429 60.1437 4.9147 60.1045 4.8978ZM23.7259 37.3253C20.2276 37.3253 17.3451 34.1136 17.3451 30.1693C17.3451 26.225 20.1717 23.0133 23.7259 23.0133C27.308 23.0133 30.1626 26.2532 30.1066 30.1693C30.1066 34.1136 27.28 37.3253 23.7259 37.3253ZM47.3178 37.3253C43.8196 37.3253 40.9371 34.1136 40.9371 30.1693C40.9371 26.225 43.7636 23.0133 47.3178 23.0133C50.9 23.0133 53.7545 26.2532 53.6986 30.1693C53.6986 34.1136 50.9 37.3253 47.3178 37.3253Z"></path></svg></button><button class="
          p-1.5 rounded-md transition-colors duration-200
          text-gray-600 hover:bg-gray-800
        " title="Help"><svg stroke="currentColor" fill="currentColor" stroke-width="0" viewBox="0 0 512 512" class="w-5 h-5" height="1em" width="1em" xmlns="http://www.w3.org/2000/svg"><path d="M256 8C119.043 8 8 119.083 8 256c0 136.997 111.043 248 248 248s248-111.003 248-248C504 119.083 392.957 8 256 8zm0 448c-110.532 0-200-89.431-200-200 0-110.495 89.472-200 200-200 110.491 0 200 89.471 200 200 0 110.53-89.431 200-200 200zm107.244-255.2c0 67.052-72.421 68.084-72.421 92.863V300c0 6.627-5.373 12-12 12h-45.647c-6.627 0-12-5.373-12-12v-8.659c0-35.745 27.1-50.034 47.579-61.516 17.561-9.845 28.324-16.541 28.324-29.579 0-17.246-21.999-28.693-39.784-28.693-23.189 0-33.894 10.977-48.942 29.969-4.057 5.12-11.46 6.071-16.666 2.124l-27.824-21.098c-5.107-3.872-6.251-11.066-2.644-16.363C184.846 131.491 214.94 112 261.794 112c49.071 0 101.45 38.304 101.45 88.8zM298 368c0 23.159-18.841 42-42 42s-42-18.841-42-42 18.841-42 42-42 42 18.841 42 42z"></path></svg></button><button class="
          p-1.5 rounded-md transition-colors duration-200
          text-gray-600 hover:bg-gray-800
        " title="Report a bug"><svg stroke="currentColor" fill="currentColor" stroke-width="0" viewBox="0 0 512 512" class="w-5 h-5" height="1em" width="1em" xmlns="http://www.w3.org/2000/svg"><path d="M511.988 288.9c-.478 17.43-15.217 31.1-32.653 31.1H424v16c0 21.864-4.882 42.584-13.6 61.145l60.228 60.228c12.496 12.497 12.496 32.758 0 45.255-12.498 12.497-32.759 12.496-45.256 0l-54.736-54.736C345.886 467.965 314.351 480 280 480V236c0-6.627-5.373-12-12-12h-24c-6.627 0-12 5.373-12 12v244c-34.351 0-65.886-12.035-90.636-32.108l-54.736 54.736c-12.498 12.497-32.759 12.496-45.256 0-12.496-12.497-12.496-32.758 0-45.255l60.228-60.228C92.882 378.584 88 357.864 88 336v-16H32.666C15.23 320 .491 306.33.013 288.9-.484 270.816 14.028 256 32 256h56v-58.745l-46.628-46.628c-12.496-12.497-12.496-32.758 0-45.255 12.498-12.497 32.758-12.497 45.256 0L141.255 160h229.489l54.627-54.627c12.498-12.497 32.758-12.497 45.256 0 12.496 12.497 12.496 32.758 0 45.255L424 197.255V256h56c17.972 0 32.484 14.816 31.988 32.9zM257 0c-61.856 0-112 50.144-112 112h224C369 50.144 318.856 0 257 0z"></path></svg></button><div class="relative"><button class="
          p-1.5 rounded-md transition-colors duration-200
          text-gray-600 hover:bg-gray-800
        " title="Settings"><svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" aria-hidden="true" data-slot="icon" class="w-6 h-6"><path stroke-linecap="round" stroke-linejoin="round" d="M9.594 3.94c.09-.542.56-.94 1.11-.94h2.593c.55 0 1.02.398 1.11.94l.213 1.281c.063.374.313.686.645.87.074.04.147.083.22.127.325.196.72.257 1.075.124l1.217-.456a1.125 1.125 0 0 1 1.37.49l1.296 2.247a1.125 1.125 0 0 1-.26 1.431l-1.003.827c-.293.241-.438.613-.43.992a7.723 7.723 0 0 1 0 .255c-.008.378.137.75.43.991l1.004.827c.424.35.534.955.26 1.43l-1.298 2.247a1.125 1.125 0 0 1-1.369.491l-1.217-.456c-.355-.133-.75-.072-1.076.124a6.47 6.47 0 0 1-.22.128c-.331.183-.581.495-.644.869l-.213 1.281c-.09.543-.56.94-1.11.94h-2.594c-.55 0-1.019-.398-1.11-.94l-.213-1.281c-.062-.374-.312-.686-.644-.87a6.52 6.52 0 0 1-.22-.127c-.325-.196-.72-.257-1.076-.124l-1.217.456a1.125 1.125 0 0 1-1.369-.49l-1.297-2.247a1.125 1.125 0 0 1 .26-1.431l1.004-.827c.292-.24.437-.613.43-.991a6.932 6.932 0 0 1 0-.255c.007-.38-.138-.751-.43-.992l-1.004-.827a1.125 1.125 0 0 1-.26-1.43l1.297-2.247a1.125 1.125 0 0 1 1.37-.491l1.216.456c.356.133.751.072 1.076-.124.072-.044.146-.086.22-.128.332-.183.582-.495.644-.869l.214-1.28Z"></path><path stroke-linecap="round" stroke-linejoin="round" d="M15 12a3 3 0 1 1-6 0 3 3 0 0 1 6 0Z"></path></svg></button></div></div></div></div><div class="flex flex-1 overflow-hidden px-4 pb-2 [&amp;&gt;.gutter]:hover:cursor-col-resize [&amp;&gt;.gutter]:cursor-col-resize" style=""><div class="h-full rounded-lg overflow-hidden" style="width: calc(29.78% - 4px);"><div class="h-full rounded-lg flex flex-col overflow-hidden bg-[#1e1e1e]"><div class="flex-none flex items-center justify-between p-2 font-mono text-sm border-b bg-[#1e1e1e] text-gray-400 border-gray-700"><span class="px-4">playground.cu</span><span class="px-4">CUDA 11.8</span></div><div class="flex-1 relative overflow-hidden"><section style="display: flex; position: relative; text-align: initial; width: 100%; height: 100%;"><div style="width: 100%; --vscode-editorCodeLens-lineHeight: 16px; --vscode-editorCodeLens-fontSize: 12px; --vscode-editorCodeLens-fontFeatureSettings: &quot;liga&quot; off, &quot;calt&quot; off;" data-keybinding-context="1" data-mode-id="cuda-cpp"><div class="monaco-editor no-user-select  showUnused showDeprecated vs-dark focused" role="code" style="width: 748px; height: 1186px;" data-uri="inmemory://model/1"><div data-mprt="3" class="overflow-guard" style="width: 748px; height: 1186px;"><div class="margin" style="position: absolute; transform: translate3d(0px, 0px, 0px); contain: strict; top: 0px; height: 5016px; width: 64px;" role="presentation" aria-hidden="true"><div class="glyph-margin" style="left: 0px; width: 0px; height: 5016px;"></div><div class="margin-view-zones" style="position: absolute;" role="presentation" aria-hidden="true"></div><div class="margin-view-overlays focused" style="position: absolute; font-family: Consolas, &quot;Courier New&quot;, monospace; font-weight: normal; font-size: 14px; font-feature-settings: &quot;liga&quot; 0, &quot;calt&quot; 0; font-variation-settings: normal; line-height: 19px; letter-spacing: 0px; width: 64px; height: 5016px;" role="presentation" aria-hidden="true"><div style="position:absolute;top:950px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">51</div></div><div style="position:absolute;top:969px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">52</div></div><div style="position:absolute;top:988px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">53</div></div><div style="position:absolute;top:1007px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">54</div></div><div style="position:absolute;top:1026px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">55</div></div><div style="position:absolute;top:1045px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">56</div></div><div style="position:absolute;top:1064px;width:100%;height:19px;"><div class="cldr codicon codicon-folding-expanded" style="left:38px;width:26px;"></div><div class="line-numbers" style="left:0px;width:38px;">57</div></div><div style="position:absolute;top:1083px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">58</div></div><div style="position:absolute;top:1102px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">59</div></div><div style="position:absolute;top:1121px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">60</div></div><div style="position:absolute;top:1140px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">61</div></div><div style="position:absolute;top:855px;width:100%;height:19px;"><div class="cldr codicon codicon-folding-expanded" style="left:38px;width:26px;"></div><div class="line-numbers" style="left:0px;width:38px;">46</div></div><div style="position:absolute;top:874px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">47</div></div><div style="position:absolute;top:893px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">48</div></div><div style="position:absolute;top:912px;width:100%;height:19px;"><div class="cldr codicon codicon-folding-expanded" style="left:38px;width:26px;"></div><div class="line-numbers" style="left:0px;width:38px;">49</div></div><div style="position:absolute;top:931px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">50</div></div><div style="position:absolute;top:817px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">44</div></div><div style="position:absolute;top:836px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">45</div></div><div style="position:absolute;top:798px;width:100%;height:19px;"><div class="cldr codicon codicon-folding-expanded" style="left:38px;width:26px;"></div><div class="line-numbers" style="left:0px;width:38px;">43</div></div><div style="position:absolute;top:741px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">40</div></div><div style="position:absolute;top:760px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">41</div></div><div style="position:absolute;top:779px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">42</div></div><div style="position:absolute;top:684px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">37</div></div><div style="position:absolute;top:703px;width:100%;height:19px;"><div class="cldr codicon codicon-folding-expanded" style="left:38px;width:26px;"></div><div class="line-numbers" style="left:0px;width:38px;">38</div></div><div style="position:absolute;top:722px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">39</div></div><div style="position:absolute;top:589px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">32</div></div><div style="position:absolute;top:608px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">33</div></div><div style="position:absolute;top:627px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">34</div></div><div style="position:absolute;top:646px;width:100%;height:19px;"><div class="cldr codicon codicon-folding-expanded" style="left:38px;width:26px;"></div><div class="line-numbers" style="left:0px;width:38px;">35</div></div><div style="position:absolute;top:665px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">36</div></div><div style="position:absolute;top:437px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">24</div></div><div style="position:absolute;top:456px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">25</div></div><div style="position:absolute;top:475px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">26</div></div><div style="position:absolute;top:494px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">27</div></div><div style="position:absolute;top:513px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">28</div></div><div style="position:absolute;top:532px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">29</div></div><div style="position:absolute;top:551px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">30</div></div><div style="position:absolute;top:570px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">31</div></div><div style="position:absolute;top:285px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">16</div></div><div style="position:absolute;top:304px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">17</div></div><div style="position:absolute;top:323px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">18</div></div><div style="position:absolute;top:342px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">19</div></div><div style="position:absolute;top:361px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">20</div></div><div style="position:absolute;top:380px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">21</div></div><div style="position:absolute;top:399px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">22</div></div><div style="position:absolute;top:418px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">23</div></div><div style="position:absolute;top:133px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">8</div></div><div style="position:absolute;top:152px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">9</div></div><div style="position:absolute;top:171px;width:100%;height:19px;"><div class="current-line current-line-margin-both" style="width:64px; height:19px;"></div><div class="line-numbers active-line-number" style="left:0px;width:38px;">10</div></div><div style="position:absolute;top:190px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">11</div></div><div style="position:absolute;top:209px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">12</div></div><div style="position:absolute;top:228px;width:100%;height:19px;"><div class="cldr codicon codicon-folding-expanded" style="left:38px;width:26px;"></div><div class="line-numbers" style="left:0px;width:38px;">13</div></div><div style="position:absolute;top:247px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">14</div></div><div style="position:absolute;top:266px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">15</div></div><div style="position:absolute;top:95px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">6</div></div><div style="position:absolute;top:114px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">7</div></div><div style="position:absolute;top:38px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">3</div></div><div style="position:absolute;top:57px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">4</div></div><div style="position:absolute;top:76px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">5</div></div><div style="position:absolute;top:0px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">1</div></div><div style="position:absolute;top:19px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">2</div></div><div style="position:absolute;top:1159px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">62</div></div><div style="position:absolute;top:1178px;width:100%;height:19px;"><div class="line-numbers" style="left:0px;width:38px;">63</div></div></div><div class="glyph-margin-widgets" style="position: absolute; top: 0px;"></div></div><div class="monaco-scrollable-element editor-scrollable vs-dark" role="presentation" style="position: absolute; overflow: hidden; left: 64px; height: 1186px; width: 684px;" data-mprt="5"><div class="lines-content monaco-editor-background" style="position: absolute; overflow: hidden; width: 1000000px; height: 1000000px; transform: translate3d(0px, 0px, 0px); contain: strict; top: 0px; left: 0px;"><div class="view-overlays focused" style="position: absolute; font-family: Consolas, &quot;Courier New&quot;, monospace; font-weight: normal; font-size: 14px; font-feature-settings: &quot;liga&quot; 0, &quot;calt&quot; 0; font-variation-settings: normal; line-height: 19px; letter-spacing: 0px; height: 0px; width: 684px;" role="presentation" aria-hidden="true"><div style="position:absolute;top:950px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div><div class="core-guide core-guide-indent lvl-1 vertical" style="left:30.796875px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:969px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div><div class="core-guide core-guide-indent lvl-1 vertical" style="left:30.796875px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:988px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:1007px;width:100%;height:19px;"></div><div style="position:absolute;top:1026px;width:100%;height:19px;"></div><div style="position:absolute;top:1045px;width:100%;height:19px;"></div><div style="position:absolute;top:1064px;width:100%;height:19px;"></div><div style="position:absolute;top:1083px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:1102px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:1121px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:1140px;width:100%;height:19px;"></div><div style="position:absolute;top:855px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:874px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div><div class="core-guide core-guide-indent lvl-1 vertical" style="left:30.796875px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:893px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div><div class="core-guide core-guide-indent lvl-1 vertical" style="left:30.796875px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:912px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div><div class="core-guide core-guide-indent lvl-1 vertical" style="left:30.796875px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:931px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div><div class="core-guide core-guide-indent lvl-1 vertical" style="left:30.796875px;height:19px;width:7.69921875px"></div><div class="core-guide core-guide-indent lvl-2 vertical" style="left:61.59375px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:817px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:836px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:798px;width:100%;height:19px;"></div><div style="position:absolute;top:741px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:760px;width:100%;height:19px;"></div><div style="position:absolute;top:779px;width:100%;height:19px;"></div><div style="position:absolute;top:684px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:703px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:722px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div><div class="core-guide core-guide-indent lvl-1 vertical" style="left:30.796875px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:589px;width:100%;height:19px;"></div><div style="position:absolute;top:608px;width:100%;height:19px;"></div><div style="position:absolute;top:627px;width:100%;height:19px;"></div><div style="position:absolute;top:646px;width:100%;height:19px;"></div><div style="position:absolute;top:665px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:437px;width:100%;height:19px;"></div><div style="position:absolute;top:456px;width:100%;height:19px;"></div><div style="position:absolute;top:475px;width:100%;height:19px;"></div><div style="position:absolute;top:494px;width:100%;height:19px;"></div><div style="position:absolute;top:513px;width:100%;height:19px;"></div><div style="position:absolute;top:532px;width:100%;height:19px;"></div><div style="position:absolute;top:551px;width:100%;height:19px;"></div><div style="position:absolute;top:570px;width:100%;height:19px;"></div><div style="position:absolute;top:285px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:304px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:323px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:342px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:361px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:380px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:399px;width:100%;height:19px;"></div><div style="position:absolute;top:418px;width:100%;height:19px;"></div><div style="position:absolute;top:133px;width:100%;height:19px;"></div><div style="position:absolute;top:152px;width:100%;height:19px;"></div><div style="position:absolute;top:171px;width:100%;height:19px;"><div class="current-line" style="width:684px; height:19px;"></div><div class="cdr wordHighlightText" style="left:146px;width:70px;height:19px;"></div></div><div style="position:absolute;top:190px;width:100%;height:19px;"></div><div style="position:absolute;top:209px;width:100%;height:19px;"></div><div style="position:absolute;top:228px;width:100%;height:19px;"></div><div style="position:absolute;top:247px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:266px;width:100%;height:19px;"><div class="core-guide core-guide-indent lvl-0 vertical" style="left:0px;height:19px;width:7.69921875px"></div></div><div style="position:absolute;top:95px;width:100%;height:19px;"></div><div style="position:absolute;top:114px;width:100%;height:19px;"></div><div style="position:absolute;top:38px;width:100%;height:19px;"></div><div style="position:absolute;top:57px;width:100%;height:19px;"></div><div style="position:absolute;top:76px;width:100%;height:19px;"></div><div style="position:absolute;top:0px;width:100%;height:19px;"></div><div style="position:absolute;top:19px;width:100%;height:19px;"></div><div style="position:absolute;top:1159px;width:100%;height:19px;"></div><div style="position:absolute;top:1178px;width:100%;height:19px;"></div></div><div role="presentation" aria-hidden="true" class="view-rulers"></div><div class="view-zones" style="position: absolute;" role="presentation" aria-hidden="true"></div><div class="view-lines monaco-mouse-cursor-text" style="position: absolute; font-family: Consolas, &quot;Courier New&quot;, monospace; font-weight: normal; font-size: 14px; font-feature-settings: &quot;liga&quot; 0, &quot;calt&quot; 0; font-variation-settings: normal; line-height: 19px; letter-spacing: 0px; width: 684px; height: 5016px;" role="presentation" aria-hidden="true" data-mprt="7"><div style="top:950px;height:19px;" class="view-line"><span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="mtk9 bracket-highlighting-2">}</span></span></div><div style="top:969px;height:19px;" class="view-line"><span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="mtk8">__syncthreads</span><span class="mtk9 bracket-highlighting-2">(</span><span class="mtk9 bracket-highlighting-2">)</span><span class="mtk9">;</span></span></div><div style="top:988px;height:19px;" class="view-line"><span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="mtk9 bracket-highlighting-1">}</span></span></div><div style="top:1007px;height:19px;" class="view-line"><span><span class="mtk9 bracket-highlighting-0">}</span></span></div><div style="top:1026px;height:19px;" class="view-line"><span><span></span></span></div><div style="top:1045px;height:19px;" class="view-line"><span><span></span></span></div><div style="top:1064px;height:19px;" class="view-line"><span><span class="mtk8">void</span><span class="mtk1">&nbsp;</span><span class="mtk11">displayGrid</span><span class="mtk9 bracket-highlighting-0">(</span><span class="mtk8">int</span><span class="mtk1">&nbsp;</span><span class="mtk4">block</span><span class="mtk9">,</span><span class="mtk1">&nbsp;</span><span class="mtk8">int</span><span class="mtk1">&nbsp;</span><span class="mtk4">n</span><span class="mtk9 bracket-highlighting-0">)</span><span class="mtk9 bracket-highlighting-0">{</span></span></div><div style="top:1083px;height:19px;" class="view-line"><span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="mtk7">//&nbsp;display&nbsp;grid&nbsp;structure</span></span></div><div style="top:1102px;height:19px;" class="view-line"><span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="mtk4">std</span><span class="mtk1">::</span><span class="mtk4">cout</span><span class="mtk9">&lt;&lt;</span><span class="mtk5">"Grid&nbsp;size:&nbsp;("</span><span class="mtk9">&lt;&lt;</span><span class="mtk9 bracket-highlighting-1">(</span><span class="mtk4">n</span><span class="mtk9">-</span><span class="mtk6">1</span><span class="mtk9">+</span><span class="mtk6">2</span><span class="mtk9">*</span><span class="mtk4">block</span><span class="mtk9 bracket-highlighting-1">)</span><span class="mtk9">/</span><span class="mtk9 bracket-highlighting-1">(</span><span class="mtk6">2</span><span class="mtk9">*</span><span class="mtk4">block</span><span class="mtk9 bracket-highlighting-1">)</span><span class="mtk9">&lt;&lt;</span><span class="mtk5">",&nbsp;1,&nbsp;1)\n"</span><span class="mtk9">;</span></span></div><div style="top:1121px;height:19px;" class="view-line"><span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="mtk4">std</span><span class="mtk1">::</span><span class="mtk4">cout</span><span class="mtk9">&lt;&lt;</span><span class="mtk5">"Block&nbsp;size:("</span><span class="mtk9">&lt;&lt;</span><span class="mtk4">block</span><span class="mtk9">&lt;&lt;</span><span class="mtk5">",&nbsp;1,&nbsp;1)\n"</span><span class="mtk9">;</span></span></div><div style="top:1140px;height:19px;" class="view-line"><span><span class="mtk9 bracket-highlighting-0">}</span></span></div><div style="top:855px;height:19px;" class="view-line"><span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="mtk8">for</span><span class="mtk9 bracket-highlighting-1">(</span><span class="mtk8">int</span><span class="mtk1">&nbsp;</span><span class="mtk4">s</span><span class="mtk9">=</span><span class="mtk6">1</span><span class="mtk9">;</span><span class="mtk1">&nbsp;</span><span class="mtk4">s</span><span class="mtk9">&lt;=</span><span class="mtk4">BLOCK</span><span class="mtk9">;</span><span class="mtk1">&nbsp;</span><span class="mtk4">s</span><span class="mtk9">*=</span><span class="mtk6">2</span><span class="mtk9 bracket-highlighting-1">)</span><span class="mtk9 bracket-highlighting-1">{</span></span></div><div style="top:874px;height:19px;" class="view-line"><span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="mtk7">//&nbsp;check&nbsp;if&nbsp;thread&nbsp;ids&nbsp;are&nbsp;divisible&nbsp;by&nbsp;2*s&nbsp;</span></span></div><div style="top:893px;height:19px;" class="view-line"><span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="mtk4">index</span><span class="mtk1">&nbsp;</span><span class="mtk9">=</span><span class="mtk1">&nbsp;</span><span class="mtk6">2</span><span class="mtk9">*</span><span class="mtk4">tid</span><span class="mtk9">*</span><span class="mtk4">s</span><span class="mtk9">;</span></span></div><div style="top:912px;height:19px;" class="view-line"><span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="mtk8">if</span><span class="mtk9 bracket-highlighting-2">(</span><span class="mtk4">index</span><span class="mtk9">+</span><span class="mtk4">s</span><span class="mtk9">&lt;</span><span class="mtk4">n</span><span class="mtk9 bracket-highlighting-2">)</span><span class="mtk9 bracket-highlighting-2">{</span></span></div><div style="top:931px;height:19px;" class="view-line"><span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="mtk4">buffer</span><span class="mtk9 bracket-highlighting-3">[</span><span class="mtk4">index</span><span class="mtk9 bracket-highlighting-3">]</span><span class="mtk1">&nbsp;</span><span class="mtk9">+=</span><span class="mtk1">&nbsp;</span><span class="mtk4">buffer</span><span class="mtk9 bracket-highlighting-3">[</span><span class="mtk4">index</span><span class="mtk9">+</span><span class="mtk4">s</span><span class="mtk9 bracket-highlighting-3">]</span><span class="mtk9">;</span></span></div><div style="top:817px;height:19px;" class="view-line"><span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="mtk8">int</span><span class="mtk1">&nbsp;</span><span class="mtk4">tid</span><span class="mtk1">&nbsp;</span><span class="mtk9">=</span><span class="mtk1">&nbsp;</span><span class="mtk8">threadIdx</span><span class="mtk9">.</span><span class="mtk4">x</span><span class="mtk1">&nbsp;</span><span class="mtk9">+</span><span class="mtk1">&nbsp;</span><span class="mtk8">blockIdx</span><span class="mtk9">.</span><span class="mtk4">x</span><span class="mtk9">*</span><span class="mtk8">blockDim</span><span class="mtk9">.</span><span class="mtk4">x</span><span class="mtk9">;</span></span></div><div style="top:836px;height:19px;" class="view-line"><span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="mtk8">int</span><span class="mtk1">&nbsp;</span><span class="mtk4">index</span><span class="mtk9">;</span></span></div><div style="top:798px;height:19px;" class="view-line"><span><span class="mtk8">__global__</span><span class="mtk1">&nbsp;</span><span class="mtk8">void</span><span class="mtk1">&nbsp;</span><span class="mtk11">reduce</span><span class="mtk9 bracket-highlighting-0">(</span><span class="mtk8">int</span><span class="mtk1">&nbsp;</span><span class="mtk9">*</span><span class="mtk4">buffer</span><span class="mtk9">,</span><span class="mtk1">&nbsp;</span><span class="mtk8">int</span><span class="mtk1">&nbsp;</span><span class="mtk4">n</span><span class="mtk9 bracket-highlighting-0">)</span><span class="mtk9 bracket-highlighting-0">{</span></span></div><div style="top:741px;height:19px;" class="view-line"><span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="mtk9 bracket-highlighting-1">}</span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;</span></span></div><div style="top:760px;height:19px;" class="view-line"><span><span class="mtk9 bracket-highlighting-0">}</span></span></div><div style="top:779px;height:19px;" class="view-line"><span><span></span></span></div><div style="top:684px;height:19px;" class="view-line"><span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="mtk4">std</span><span class="mtk1">::</span><span class="mtk4">cout</span><span class="mtk9">&lt;&lt;</span><span class="mtk5">"Displaying&nbsp;buffer&nbsp;-&gt;&nbsp;\n"</span><span class="mtk9">;</span></span></div><div style="top:703px;height:19px;" class="view-line"><span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="mtk8">for</span><span class="mtk9 bracket-highlighting-1">(</span><span class="mtk8">int</span><span class="mtk1">&nbsp;</span><span class="mtk4">i</span><span class="mtk9">=</span><span class="mtk6">0</span><span class="mtk9">;</span><span class="mtk1">&nbsp;</span><span class="mtk4">i</span><span class="mtk9">&lt;</span><span class="mtk4">n</span><span class="mtk9">;</span><span class="mtk1">&nbsp;</span><span class="mtk4">i</span><span class="mtk9">++</span><span class="mtk9 bracket-highlighting-1">)</span><span class="mtk9 bracket-highlighting-1">{</span></span></div><div style="top:722px;height:19px;" class="view-line"><span><span class="mtk1">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="mtk4">std</span><span class="mtk1">::</span><span class="mtk4">cout</span><span class="mtk9">&lt;&lt;</span><span class="mtk4">buffer</span><span class="mtk9 bracket-highlighting-2">[</span><span class="mtk4">i</span><span class="mtk9 bracket-highlighting-2">]</span><span class="mtk9">&lt;&lt;</span><span class="mtk4">std</span><span class="mtk1">::</span><span class="mtk4">endl</span><span class="mtk9">;</span></span></div><div style="top:589px;height:19px;" class="view-line"><span><span class="mtk7">*/</span></span></div><div style="top:608px;height:19px;" class="view-line"><span><span></span></span></div><div style="top:627px;height:19px;" class="view-line"><span><span></span></span></div><div style="top:646px;height:19px;" class="view-line"><span><span class="mtk8">void</span><span class="mtk1">&nbsp;</span><span class="mtk11">displayArray</span><span class="mtk9 bracket-highlighting-0">(</span><span class="mtk8">int</span><span class="mtk9">*</span><span class="mtk1">&nbsp;</span><span class="mtk4">buffer</span><span class="mtk9">,</span><span class="mtk1">&nbsp;</span><span class="mtk8">int</span><span class="mtk1">&nbsp;</span><span class="mtk4">n</span><span class="mtk9 bracket-highlighting-0">)</span><span class="mtk9 bracket-highlighting-0">{</span></span></div><div style="top:665px;height:19px;" class="view-line"><span><span></span></span></div><div style="top:437px;height:19px;" class="view-line"><span><span class="mtk7">******************</span></span></div><div style="top:456px;height:19px;" class="view-line"><span><span class="mtk7">*&nbsp;(s)&nbsp;|&nbsp;Threads&nbsp;&nbsp;*</span></span></div><div style="top:475px;height:19px;" class="view-line"><span><span class="mtk7">******************</span></span></div><div style="top:494px;height:19px;" class="view-line"><span><span></span></span></div><div style="top:513px;height:19px;" class="view-line"><span><span class="mtk7">(1)&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|</span></span></div><div style="top:532px;height:19px;" class="view-line"><span><span class="mtk7">(2)&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|</span></span></div><div style="top:551px;height:19px;" class="view-line"><span><span class="mtk7">(4)&nbsp;&nbsp;&nbsp;|</span></span></div><div style="top:570px;height:19px;" class="view-line"><span><span></span></span></div><div style="top:285px;height:19px;" class="view-line"><span><span class="mtk7">&nbsp;&nbsp;&nbsp;&nbsp;BLOCK&nbsp;0&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;BLOCK&nbsp;1</span></span></div><div style="top:304px;height:19px;" class="view-line"><span><span></span></span></div><div style="top:323px;height:19px;" class="view-line"><span><span class="mtk7">&nbsp;&nbsp;&nbsp;&nbsp;***************************</span></span></div><div style="top:342px;height:19px;" class="view-line"><span><span class="mtk7">&nbsp;&nbsp;&nbsp;&nbsp;*&nbsp;0,&nbsp;1,&nbsp;2,&nbsp;3&nbsp;*&nbsp;4,&nbsp;5,&nbsp;6,&nbsp;7&nbsp;*</span></span></div><div style="top:361px;height:19px;" class="view-line"><span><span class="mtk7">&nbsp;&nbsp;&nbsp;&nbsp;***************************</span></span></div><div style="top:380px;height:19px;" class="view-line"><span><span></span></span></div><div style="top:399px;height:19px;" class="view-line"><span><span class="mtk7">Threads&nbsp;will&nbsp;execute&nbsp;as&nbsp;follows&nbsp;for&nbsp;eachs&nbsp;stride:</span></span></div><div style="top:418px;height:19px;" class="view-line"><span><span></span></span></div><div style="top:133px;height:19px;" class="view-line"><span><span></span></span></div><div style="top:152px;height:19px;" class="view-line"><span><span class="mtk7">Input&nbsp;array&nbsp;is&nbsp;of&nbsp;size&nbsp;N</span></span></div><div style="top:171px;height:19px;" class="view-line"><span><span class="mtk7">Assign&nbsp;N/2&nbsp;threads&nbsp;initially</span></span></div><div style="top:190px;height:19px;" class="view-line"><span><span class="mtk7">Each&nbsp;block&nbsp;will&nbsp;compute&nbsp;reduction&nbsp;of&nbsp;2*BLOCK&nbsp;sized</span><span class="mtk7">&nbsp;input&nbsp;tile&nbsp;</span></span></div><div style="top:209px;height:19px;" class="view-line"><span><span></span></span></div><div style="top:228px;height:19px;" class="view-line"><span><span class="mtk7">EXAMPLE&nbsp;ARRAY:-</span></span></div><div style="top:247px;height:19px;" class="view-line"><span><span></span></span></div><div style="top:266px;height:19px;" class="view-line"><span><span></span></span></div><div style="top:95px;height:19px;" class="view-line"><span><span></span></span></div><div style="top:114px;height:19px;" class="view-line"><span><span class="mtk7">/*</span></span></div><div style="top:38px;height:19px;" class="view-line"><span><span class="mtk13">#include</span><span class="mtk1">&nbsp;</span><span class="mtk5">&lt;iostream&gt;</span></span></div><div style="top:57px;height:19px;" class="view-line"><span><span class="mtk13">#include</span><span class="mtk1">&nbsp;</span><span class="mtk5">&lt;cuda_runtime.h&gt;</span></span></div><div style="top:76px;height:19px;" class="view-line"><span><span class="mtk13">#include</span><span class="mtk5">&lt;vector&gt;</span></span></div><div style="top:0px;height:19px;" class="view-line"><span><span class="mtk13">#define</span><span class="mtk1">&nbsp;</span><span class="mtk4">N</span><span class="mtk1">&nbsp;</span><span class="mtk6">1024</span></span></div><div style="top:19px;height:19px;" class="view-line"><span><span class="mtk13">#define</span><span class="mtk1">&nbsp;</span><span class="mtk4">BLOCK</span><span class="mtk1">&nbsp;</span><span class="mtk6">4</span></span></div><div style="top:1159px;height:19px;" class="view-line"><span><span></span></span></div><div style="top:1178px;height:19px;" class="view-line"><span><span></span></span></div></div><div data-mprt="1" class="contentWidgets" style="position: absolute; top: 0px;"></div><div role="presentation" aria-hidden="true" class="cursors-layer cursor-line-style cursor-solid"><div class="cursor monaco-mouse-cursor-text " style="height: 19px; top: 171px; left: 215px; font-family: Consolas, &quot;Courier New&quot;, monospace; font-weight: normal; font-size: 14px; font-feature-settings: &quot;liga&quot; 0, &quot;calt&quot; 0; font-variation-settings: normal; line-height: 19px; letter-spacing: 0px; display: block; visibility: inherit; padding-left: 1px; width: 2px;"></div></div></div><div role="presentation" aria-hidden="true" class="invisible scrollbar horizontal" style="position: absolute; width: 670px; height: 12px; left: 0px; bottom: 0px;"><div class="slider" style="position: absolute; top: 0px; left: 0px; height: 12px; transform: translate3d(0px, 0px, 0px); contain: strict; width: 670px;"></div></div><canvas class="decorationsOverviewRuler" style="position: absolute; transform: translate3d(0px, 0px, 0px); contain: strict; top: 0px; right: 0px; width: 14px; height: 1186px; display: block;" aria-hidden="true" width="21" height="1779"></canvas><div role="presentation" aria-hidden="true" class="invisible scrollbar vertical fade" style="position: absolute; width: 14px; height: 1186px; right: 0px; top: 0px;"><div class="slider" style="position: absolute; top: 0px; left: 0px; width: 14px; transform: translate3d(0px, 0px, 0px); contain: strict; height: 280px;"></div></div></div><div role="presentation" aria-hidden="true" style="width: 748px;" class=""></div><textarea data-mprt="6" class="inputarea monaco-mouse-cursor-text" wrap="off" style="tab-size: 30.7969px; font-family: Consolas, &quot;Courier New&quot;, monospace; font-weight: normal; font-size: 14px; font-feature-settings: &quot;liga&quot; 0, &quot;calt&quot; 0; font-variation-settings: normal; line-height: 19px; letter-spacing: 0px; top: 171px; left: 280px; width: 0px; height: 0px;" autocorrect="off" autocapitalize="none" autocomplete="off" spellcheck="false" aria-label="Editor content;Press Alt+F1 for Accessibility Options." aria-required="false" tabindex="0" role="textbox" aria-roledescription="editor" aria-multiline="true" aria-autocomplete="both" aria-haspopup="false">#define N 1024
#define BLOCK 4
#include &lt;iostream&gt;
#include &lt;cuda_runtime.h&gt;
#include&lt;vector&gt;

/*

Input array is of size N
Assign N/2 threads initially
</textarea><div style="position: absolute; top: 0px; left: 0px; width: 0px; height: 0px;" class="monaco-editor-background textAreaCover line-numbers"></div><div data-mprt="4" class="overlayWidgets" style="width: 748px;"><div class="monaco-hover hidden" tabindex="0" role="tooltip" style="position: absolute;" widgetid="editor.contrib.modesGlyphHoverWidget"><div class="monaco-scrollable-element " role="presentation" style="position: relative; overflow: hidden;"><div class="monaco-hover-content" style="overflow: hidden;"></div><div role="presentation" aria-hidden="true" class="invisible scrollbar horizontal" style="position: absolute;"><div class="slider" style="position: absolute; top: 0px; left: 0px; height: 10px; transform: translate3d(0px, 0px, 0px); contain: strict;"></div></div><div role="presentation" aria-hidden="true" class="invisible scrollbar vertical" style="position: absolute;"><div class="slider" style="position: absolute; top: 0px; left: 0px; width: 10px; transform: translate3d(0px, 0px, 0px); contain: strict;"></div></div><div class="shadow"></div><div class="shadow"></div><div class="shadow"></div></div></div></div><div data-mprt="8" class="minimap slider-mouseover" style="position: absolute; left: 0px; width: 0px; height: 1186px;" role="presentation" aria-hidden="true"><div class="minimap-shadow-hidden" style="height: 1186px;"></div><canvas style="position: absolute; left: 0px; width: 0px; height: 1186px;" width="0" height="1779"></canvas><canvas style="position: absolute; left: 0px; width: 0px; height: 1186px;" class="minimap-decorations-layer" width="0" height="1779"></canvas><div style="position: absolute; transform: translate3d(0px, 0px, 0px); contain: strict; width: 0px;" class="minimap-slider"><div style="position: absolute; width: 0px; height: 0px;" class="minimap-slider-horizontal"></div></div></div><div role="presentation" aria-hidden="true" class="blockDecorations-container"></div></div><div data-mprt="2" class="overflowingContentWidgets"><div style="position: absolute; height: 27px; width: 150px; z-index: 50; display: none; visibility: hidden; max-width: 2560px;" widgetid="editor.contrib.resizableContentHoverWidget"><div class="monaco-sash vertical" style="left: 148px;"></div><div class="monaco-sash vertical" style="left: -2px;"></div><div class="monaco-sash orthogonal-edge-north horizontal" style="top: -2px;"><div class="orthogonal-drag-handle start"></div><div class="orthogonal-drag-handle end"></div></div><div class="monaco-sash orthogonal-edge-south horizontal" style="top: 25px;"><div class="orthogonal-drag-handle start"></div><div class="orthogonal-drag-handle end"></div></div><div class="monaco-hover hidden" tabindex="0" role="tooltip" style="max-width: 500px; max-height: 296.5px; --vscode-hover-maxWidth: 500px;"><div class="monaco-scrollable-element " role="presentation" style="position: relative; overflow: hidden;"><div class="monaco-hover-content" style="overflow: hidden; font-size: 14px; line-height: 1.35714; max-width: 500px; max-height: 296.5px;"></div><div role="presentation" aria-hidden="true" class="invisible scrollbar horizontal" style="position: absolute;"><div class="slider" style="position: absolute; top: 0px; left: 0px; height: 10px; transform: translate3d(0px, 0px, 0px); contain: strict;"></div></div><div role="presentation" aria-hidden="true" class="invisible scrollbar vertical" style="position: absolute;"><div class="slider" style="position: absolute; top: 0px; left: 0px; width: 10px; transform: translate3d(0px, 0px, 0px); contain: strict;"></div></div><div class="shadow"></div><div class="shadow"></div><div class="shadow"></div></div></div></div><div class="editor-widget suggest-widget" style="position: absolute; display: none; visibility: hidden; max-width: 2560px; height: 40px; width: 430px; top: 1059px; left: 434px;" widgetid="editor.widget.suggestWidget"><div class="monaco-sash vertical" style="left: 428px;"></div><div class="monaco-sash vertical disabled" style="left: -2px;"></div><div class="monaco-sash orthogonal-edge-north horizontal disabled" style="top: -2px;"><div class="orthogonal-drag-handle end"></div></div><div class="monaco-sash orthogonal-edge-south horizontal" style="top: 38px;"><div class="orthogonal-drag-handle end"></div></div><div class="message" style="display: none;" aria-hidden="true"></div><div class="tree" style="height: 40px; display: none;" aria-hidden="true"><div class="monaco-list list_id_1 selection-none" tabindex="0" role="listbox" aria-label="Suggest"><div class="monaco-scrollable-element " role="presentation" style="position: relative; overflow: hidden;"><div class="monaco-list-rows" style="transform: translate3d(0px, 0px, 0px); overflow: hidden; contain: strict; height: 0px; left: 0px; top: 0px;"></div><div role="presentation" aria-hidden="true" class="invisible scrollbar horizontal" style="position: absolute; width: 0px; height: 10px; left: 0px; bottom: 0px;"><div class="slider" style="position: absolute; top: 0px; left: 0px; height: 10px; transform: translate3d(0px, 0px, 0px); contain: strict; width: 0px;"></div></div><div role="presentation" aria-hidden="true" class="invisible scrollbar vertical" style="position: absolute; width: 10px; height: 40px; right: 0px; top: 0px;"><div class="slider" style="position: absolute; top: 0px; left: 0px; width: 10px; transform: translate3d(0px, 0px, 0px); contain: strict; height: 40px;"></div></div></div><style type="text/css" media="screen">.monaco-list.list_id_1:focus .monaco-list-row.focused { background-color: var(--vscode-list-focusBackground); }
.monaco-list.list_id_1:focus .monaco-list-row.focused:hover { background-color: var(--vscode-list-focusBackground); }
.monaco-list.list_id_1:focus .monaco-list-row.focused { color: var(--vscode-list-focusForeground); }
.monaco-list.list_id_1:focus .monaco-list-row.selected { background-color: var(--vscode-list-activeSelectionBackground); }
.monaco-list.list_id_1:focus .monaco-list-row.selected:hover { background-color: var(--vscode-list-activeSelectionBackground); }
.monaco-list.list_id_1:focus .monaco-list-row.selected { color: var(--vscode-list-activeSelectionForeground); }
.monaco-list.list_id_1:focus .monaco-list-row.selected .codicon { color: var(--vscode-list-activeSelectionIconForeground); }

				.monaco-drag-image,
				.monaco-list.list_id_1:focus .monaco-list-row.selected.focused { background-color: var(--vscode-list-activeSelectionBackground); }
			

				.monaco-drag-image,
				.monaco-list.list_id_1:focus .monaco-list-row.selected.focused { color: var(--vscode-list-activeSelectionForeground); }
			
.monaco-list.list_id_1 .monaco-list-row.focused .codicon { color:  var(--vscode-list-inactiveSelectionIconForeground); }
.monaco-list.list_id_1 .monaco-list-row.focused { background-color:  var(--vscode-editorSuggestWidget-selectedBackground); }
.monaco-list.list_id_1 .monaco-list-row.focused:hover { background-color:  var(--vscode-editorSuggestWidget-selectedBackground); }
.monaco-list.list_id_1 .monaco-list-row.selected { background-color:  var(--vscode-list-inactiveSelectionBackground); }
.monaco-list.list_id_1 .monaco-list-row.selected:hover { background-color:  var(--vscode-list-inactiveSelectionBackground); }
.monaco-list.list_id_1 .monaco-list-row.selected { color: var(--vscode-list-inactiveSelectionForeground); }
.monaco-list.list_id_1:not(.drop-target):not(.dragging) .monaco-list-row:hover:not(.selected):not(.focused) { background-color: var(--vscode-list-hoverBackground); }
.monaco-list.list_id_1:not(.drop-target):not(.dragging) .monaco-list-row:hover:not(.selected):not(.focused) { color:  var(--vscode-list-hoverForeground); }
.monaco-list.list_id_1:focus .monaco-list-row.focused.selected { outline: 1px solid var(--vscode-list-focusAndSelectionOutline, var(--vscode-contrastActiveBorder, var(--vscode-list-focusOutline))); outline-offset: -1px;}

				.monaco-drag-image,
				.monaco-list.list_id_1:focus .monaco-list-row.focused { outline: 1px solid var(--vscode-list-focusOutline); outline-offset: -1px; }
				.monaco-workbench.context-menu-visible .monaco-list.list_id_1.last-focused .monaco-list-row.focused { outline: 1px solid var(--vscode-list-focusOutline); outline-offset: -1px; }
			
.monaco-list.list_id_1 .monaco-list-row.focused.selected { outline: 1px dotted var(--vscode-contrastActiveBorder, var(--vscode-contrastActiveBorder)); outline-offset: -1px; }
.monaco-list.list_id_1 .monaco-list-row.selected { outline: 1px dotted var(--vscode-contrastActiveBorder); outline-offset: -1px; }
.monaco-list.list_id_1 .monaco-list-row.focused { outline: 1px dotted var(--vscode-contrastActiveBorder); outline-offset: -1px; }
.monaco-list.list_id_1 .monaco-list-row:hover { outline: 1px dashed var(--vscode-contrastActiveBorder); outline-offset: -1px; }

				.monaco-list.list_id_1.drop-target,
				.monaco-list.list_id_1 .monaco-list-rows.drop-target,
				.monaco-list.list_id_1 .monaco-list-row.drop-target { background-color: var(--vscode-list-dropBackground) !important; color: inherit !important; }
			

				.monaco-table > .monaco-split-view2,
				.monaco-table > .monaco-split-view2 .monaco-sash.vertical::before,
				.monaco-workbench:not(.reduce-motion) .monaco-table:hover > .monaco-split-view2,
				.monaco-workbench:not(.reduce-motion) .monaco-table:hover > .monaco-split-view2 .monaco-sash.vertical::before {
					border-color: var(--vscode-tree-tableColumnsBorder);
				}

				.monaco-workbench:not(.reduce-motion) .monaco-table > .monaco-split-view2,
				.monaco-workbench:not(.reduce-motion) .monaco-table > .monaco-split-view2 .monaco-sash.vertical::before {
					border-color: transparent;
				}
			

				.monaco-table .monaco-list-row[data-parity=odd]:not(.focused):not(.selected):not(:hover) .monaco-table-tr,
				.monaco-table .monaco-list:not(:focus) .monaco-list-row[data-parity=odd].focused:not(.selected):not(:hover) .monaco-table-tr,
				.monaco-table .monaco-list:not(.focused) .monaco-list-row[data-parity=odd].focused:not(.selected):not(:hover) .monaco-table-tr {
					background-color: var(--vscode-tree-tableOddRowsBackground);
				}
			</style></div></div><div class="suggest-status-bar" style="height: 19px; display: none;" aria-hidden="true"><div class="monaco-action-bar animated left"><ul class="actions-container" role="presentation"><li class="action-item menu-entry" role="presentation" title="Insert (Enter)"><a class="action-label" role="button" aria-label="Insert (Enter)" aria-checked="" tabindex="0">Insert (⏎)</a></li></ul></div><div class="monaco-action-bar animated right"><ul class="actions-container" role="presentation"><li class="action-item menu-entry" role="presentation" title="show more (Ctrl+Space)"><a class="action-label" role="button" aria-label="show more (Ctrl+Space)" aria-checked="" tabindex="0">show more (Ctrl+Space)</a></li></ul></div></div></div></div><div class="shadow-root-host"></div></div></div></section></div></div></div><div class="gutter gutter-horizontal" style="width: 8px;"></div><div class="h-full rounded-lg overflow-hidden" style="width: calc(70.22% - 4px);"><div class="h-full"><div class="h-full flex flex-col bg-[#1e1e1e]"><div class="flex-none flex items-center justify-between p-2 font-mono text-sm border-b border-gray-700 bg-[#1e1e1e] text-gray-400"><span class="px-4">Console Output</span><button class="
              flex items-center gap-2 px-3 transition-colors duration-200 rounded
              text-red-300 hover:text-red-200
            "><span>clear</span></button></div><div class="flex-1 p-4" style="min-height: 0px;"><div class="h-full w-full"><div dir="ltr" class="terminal xterm xterm-dom-renderer-owner-1"><div class="xterm-viewport" style="background-color: rgb(30, 30, 30);"><div class="xterm-scroll-area" style="height: 5304px;"></div></div><div class="xterm-screen" style="width: 1717px; height: 1144px;"><div class="xterm-helpers"><textarea class="xterm-helper-textarea" aria-label="Terminal input" aria-multiline="false" autocorrect="off" autocapitalize="none" spellcheck="false" tabindex="0" style="left: 0px; top: 78px; width: 7.69955px; height: 26px; line-height: 26px; z-index: -5;"></textarea><div class="composition-view"></div><div class="xterm-width-cache-measure-container" aria-hidden="true" style="white-space: pre; font-kerning: none; font-family: operator mono, SFMono-Regular, Consolas, Liberation Mono, Menlo, monospace; font-size: 14px;"><span class="xterm-char-measure-element" style="font-weight: normal;">||||||||||||||||||||||||||||||||</span><span class="xterm-char-measure-element" style="font-weight: bold;"></span><span class="xterm-char-measure-element" style="font-style: italic; font-weight: normal;"></span><span class="xterm-char-measure-element" style="font-weight: bold; font-style: italic;"></span></div></div><style>.xterm-dom-renderer-owner-1 .xterm-rows span { display: inline-block; height: 100%; vertical-align: top;}</style><style>.xterm-dom-renderer-owner-1 .xterm-rows { color: #ffffff; font-family: operator mono,SFMono-Regular,Consolas,Liberation Mono,Menlo,monospace; font-size: 14px; font-kerning: none; white-space: pre}.xterm-dom-renderer-owner-1 .xterm-rows .xterm-dim { color: #ffffff80;}.xterm-dom-renderer-owner-1 span:not(.xterm-bold) { font-weight: normal;}.xterm-dom-renderer-owner-1 span.xterm-bold { font-weight: bold;}.xterm-dom-renderer-owner-1 span.xterm-italic { font-style: italic;}@keyframes blink_underline_1 { 50% {  border-bottom-style: hidden; }}@keyframes blink_bar_1 { 50% {  box-shadow: none; }}@keyframes blink_block_1 { 0% {  background-color: #ffffff;  color: #000000; } 50% {  background-color: inherit;  color: #ffffff; }}.xterm-dom-renderer-owner-1 .xterm-rows.xterm-focus .xterm-cursor.xterm-cursor-blink.xterm-cursor-underline { animation: blink_underline_1 1s step-end infinite;}.xterm-dom-renderer-owner-1 .xterm-rows.xterm-focus .xterm-cursor.xterm-cursor-blink.xterm-cursor-bar { animation: blink_bar_1 1s step-end infinite;}.xterm-dom-renderer-owner-1 .xterm-rows.xterm-focus .xterm-cursor.xterm-cursor-blink.xterm-cursor-block { animation: blink_block_1 1s step-end infinite;}.xterm-dom-renderer-owner-1 .xterm-rows .xterm-cursor.xterm-cursor-block { background-color: #ffffff; color: #000000;}.xterm-dom-renderer-owner-1 .xterm-rows .xterm-cursor.xterm-cursor-block:not(.xterm-cursor-blink) { background-color: #ffffff !important; color: #000000 !important;}.xterm-dom-renderer-owner-1 .xterm-rows .xterm-cursor.xterm-cursor-outline { outline: 1px solid #ffffff; outline-offset: -1px;}.xterm-dom-renderer-owner-1 .xterm-rows .xterm-cursor.xterm-cursor-bar { box-shadow: 1px 0 0 #ffffff inset;}.xterm-dom-renderer-owner-1 .xterm-rows .xterm-cursor.xterm-cursor-underline { border-bottom: 1px #ffffff; border-bottom-style: solid; height: calc(100% - 1px);}.xterm-dom-renderer-owner-1 .xterm-selection { position: absolute; top: 0; left: 0; z-index: 1; pointer-events: none;}.xterm-dom-renderer-owner-1.focus .xterm-selection div { position: absolute; background-color: #626262;}.xterm-dom-renderer-owner-1 .xterm-selection div { position: absolute; background-color: #626262;}.xterm-dom-renderer-owner-1 .xterm-fg-0 { color: #2e3436; }.xterm-dom-renderer-owner-1 .xterm-fg-0.xterm-dim { color: #2e343680; }.xterm-dom-renderer-owner-1 .xterm-bg-0 { background-color: #2e3436; }.xterm-dom-renderer-owner-1 .xterm-fg-1 { color: #cc0000; }.xterm-dom-renderer-owner-1 .xterm-fg-1.xterm-dim { color: #cc000080; }.xterm-dom-renderer-owner-1 .xterm-bg-1 { background-color: #cc0000; }.xterm-dom-renderer-owner-1 .xterm-fg-2 { color: #4e9a06; }.xterm-dom-renderer-owner-1 .xterm-fg-2.xterm-dim { color: #4e9a0680; }.xterm-dom-renderer-owner-1 .xterm-bg-2 { background-color: #4e9a06; }.xterm-dom-renderer-owner-1 .xterm-fg-3 { color: #c4a000; }.xterm-dom-renderer-owner-1 .xterm-fg-3.xterm-dim { color: #c4a00080; }.xterm-dom-renderer-owner-1 .xterm-bg-3 { background-color: #c4a000; }.xterm-dom-renderer-owner-1 .xterm-fg-4 { color: #3465a4; }.xterm-dom-renderer-owner-1 .xterm-fg-4.xterm-dim { color: #3465a480; }.xterm-dom-renderer-owner-1 .xterm-bg-4 { background-color: #3465a4; }.xterm-dom-renderer-owner-1 .xterm-fg-5 { color: #75507b; }.xterm-dom-renderer-owner-1 .xterm-fg-5.xterm-dim { color: #75507b80; }.xterm-dom-renderer-owner-1 .xterm-bg-5 { background-color: #75507b; }.xterm-dom-renderer-owner-1 .xterm-fg-6 { color: #06989a; }.xterm-dom-renderer-owner-1 .xterm-fg-6.xterm-dim { color: #06989a80; }.xterm-dom-renderer-owner-1 .xterm-bg-6 { background-color: #06989a; }.xterm-dom-renderer-owner-1 .xterm-fg-7 { color: #d3d7cf; }.xterm-dom-renderer-owner-1 .xterm-fg-7.xterm-dim { color: #d3d7cf80; }.xterm-dom-renderer-owner-1 .xterm-bg-7 { background-color: #d3d7cf; }.xterm-dom-renderer-owner-1 .xterm-fg-8 { color: #555753; }.xterm-dom-renderer-owner-1 .xterm-fg-8.xterm-dim { color: #55575380; }.xterm-dom-renderer-owner-1 .xterm-bg-8 { background-color: #555753; }.xterm-dom-renderer-owner-1 .xterm-fg-9 { color: #ef2929; }.xterm-dom-renderer-owner-1 .xterm-fg-9.xterm-dim { color: #ef292980; }.xterm-dom-renderer-owner-1 .xterm-bg-9 { background-color: #ef2929; }.xterm-dom-renderer-owner-1 .xterm-fg-10 { color: #8ae234; }.xterm-dom-renderer-owner-1 .xterm-fg-10.xterm-dim { color: #8ae23480; }.xterm-dom-renderer-owner-1 .xterm-bg-10 { background-color: #8ae234; }.xterm-dom-renderer-owner-1 .xterm-fg-11 { color: #fce94f; }.xterm-dom-renderer-owner-1 .xterm-fg-11.xterm-dim { color: #fce94f80; }.xterm-dom-renderer-owner-1 .xterm-bg-11 { background-color: #fce94f; }.xterm-dom-renderer-owner-1 .xterm-fg-12 { color: #729fcf; }.xterm-dom-renderer-owner-1 .xterm-fg-12.xterm-dim { color: #729fcf80; }.xterm-dom-renderer-owner-1 .xterm-bg-12 { background-color: #729fcf; }.xterm-dom-renderer-owner-1 .xterm-fg-13 { color: #ad7fa8; }.xterm-dom-renderer-owner-1 .xterm-fg-13.xterm-dim { color: #ad7fa880; }.xterm-dom-renderer-owner-1 .xterm-bg-13 { background-color: #ad7fa8; }.xterm-dom-renderer-owner-1 .xterm-fg-14 { color: #34e2e2; }.xterm-dom-renderer-owner-1 .xterm-fg-14.xterm-dim { color: #34e2e280; }.xterm-dom-renderer-owner-1 .xterm-bg-14 { background-color: #34e2e2; }.xterm-dom-renderer-owner-1 .xterm-fg-15 { color: #eeeeec; }.xterm-dom-renderer-owner-1 .xterm-fg-15.xterm-dim { color: #eeeeec80; }.xterm-dom-renderer-owner-1 .xterm-bg-15 { background-color: #eeeeec; }.xterm-dom-renderer-owner-1 .xterm-fg-16 { color: #000000; }.xterm-dom-renderer-owner-1 .xterm-fg-16.xterm-dim { color: #00000080; }.xterm-dom-renderer-owner-1 .xterm-bg-16 { background-color: #000000; }.xterm-dom-renderer-owner-1 .xterm-fg-17 { color: #00005f; }.xterm-dom-renderer-owner-1 .xterm-fg-17.xterm-dim { color: #00005f80; }.xterm-dom-renderer-owner-1 .xterm-bg-17 { background-color: #00005f; }.xterm-dom-renderer-owner-1 .xterm-fg-18 { color: #000087; }.xterm-dom-renderer-owner-1 .xterm-fg-18.xterm-dim { color: #00008780; }.xterm-dom-renderer-owner-1 .xterm-bg-18 { background-color: #000087; }.xterm-dom-renderer-owner-1 .xterm-fg-19 { color: #0000af; }.xterm-dom-renderer-owner-1 .xterm-fg-19.xterm-dim { color: #0000af80; }.xterm-dom-renderer-owner-1 .xterm-bg-19 { background-color: #0000af; }.xterm-dom-renderer-owner-1 .xterm-fg-20 { color: #0000d7; }.xterm-dom-renderer-owner-1 .xterm-fg-20.xterm-dim { color: #0000d780; }.xterm-dom-renderer-owner-1 .xterm-bg-20 { background-color: #0000d7; }.xterm-dom-renderer-owner-1 .xterm-fg-21 { color: #0000ff; }.xterm-dom-renderer-owner-1 .xterm-fg-21.xterm-dim { color: #0000ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-21 { background-color: #0000ff; }.xterm-dom-renderer-owner-1 .xterm-fg-22 { color: #005f00; }.xterm-dom-renderer-owner-1 .xterm-fg-22.xterm-dim { color: #005f0080; }.xterm-dom-renderer-owner-1 .xterm-bg-22 { background-color: #005f00; }.xterm-dom-renderer-owner-1 .xterm-fg-23 { color: #005f5f; }.xterm-dom-renderer-owner-1 .xterm-fg-23.xterm-dim { color: #005f5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-23 { background-color: #005f5f; }.xterm-dom-renderer-owner-1 .xterm-fg-24 { color: #005f87; }.xterm-dom-renderer-owner-1 .xterm-fg-24.xterm-dim { color: #005f8780; }.xterm-dom-renderer-owner-1 .xterm-bg-24 { background-color: #005f87; }.xterm-dom-renderer-owner-1 .xterm-fg-25 { color: #005faf; }.xterm-dom-renderer-owner-1 .xterm-fg-25.xterm-dim { color: #005faf80; }.xterm-dom-renderer-owner-1 .xterm-bg-25 { background-color: #005faf; }.xterm-dom-renderer-owner-1 .xterm-fg-26 { color: #005fd7; }.xterm-dom-renderer-owner-1 .xterm-fg-26.xterm-dim { color: #005fd780; }.xterm-dom-renderer-owner-1 .xterm-bg-26 { background-color: #005fd7; }.xterm-dom-renderer-owner-1 .xterm-fg-27 { color: #005fff; }.xterm-dom-renderer-owner-1 .xterm-fg-27.xterm-dim { color: #005fff80; }.xterm-dom-renderer-owner-1 .xterm-bg-27 { background-color: #005fff; }.xterm-dom-renderer-owner-1 .xterm-fg-28 { color: #008700; }.xterm-dom-renderer-owner-1 .xterm-fg-28.xterm-dim { color: #00870080; }.xterm-dom-renderer-owner-1 .xterm-bg-28 { background-color: #008700; }.xterm-dom-renderer-owner-1 .xterm-fg-29 { color: #00875f; }.xterm-dom-renderer-owner-1 .xterm-fg-29.xterm-dim { color: #00875f80; }.xterm-dom-renderer-owner-1 .xterm-bg-29 { background-color: #00875f; }.xterm-dom-renderer-owner-1 .xterm-fg-30 { color: #008787; }.xterm-dom-renderer-owner-1 .xterm-fg-30.xterm-dim { color: #00878780; }.xterm-dom-renderer-owner-1 .xterm-bg-30 { background-color: #008787; }.xterm-dom-renderer-owner-1 .xterm-fg-31 { color: #0087af; }.xterm-dom-renderer-owner-1 .xterm-fg-31.xterm-dim { color: #0087af80; }.xterm-dom-renderer-owner-1 .xterm-bg-31 { background-color: #0087af; }.xterm-dom-renderer-owner-1 .xterm-fg-32 { color: #0087d7; }.xterm-dom-renderer-owner-1 .xterm-fg-32.xterm-dim { color: #0087d780; }.xterm-dom-renderer-owner-1 .xterm-bg-32 { background-color: #0087d7; }.xterm-dom-renderer-owner-1 .xterm-fg-33 { color: #0087ff; }.xterm-dom-renderer-owner-1 .xterm-fg-33.xterm-dim { color: #0087ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-33 { background-color: #0087ff; }.xterm-dom-renderer-owner-1 .xterm-fg-34 { color: #00af00; }.xterm-dom-renderer-owner-1 .xterm-fg-34.xterm-dim { color: #00af0080; }.xterm-dom-renderer-owner-1 .xterm-bg-34 { background-color: #00af00; }.xterm-dom-renderer-owner-1 .xterm-fg-35 { color: #00af5f; }.xterm-dom-renderer-owner-1 .xterm-fg-35.xterm-dim { color: #00af5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-35 { background-color: #00af5f; }.xterm-dom-renderer-owner-1 .xterm-fg-36 { color: #00af87; }.xterm-dom-renderer-owner-1 .xterm-fg-36.xterm-dim { color: #00af8780; }.xterm-dom-renderer-owner-1 .xterm-bg-36 { background-color: #00af87; }.xterm-dom-renderer-owner-1 .xterm-fg-37 { color: #00afaf; }.xterm-dom-renderer-owner-1 .xterm-fg-37.xterm-dim { color: #00afaf80; }.xterm-dom-renderer-owner-1 .xterm-bg-37 { background-color: #00afaf; }.xterm-dom-renderer-owner-1 .xterm-fg-38 { color: #00afd7; }.xterm-dom-renderer-owner-1 .xterm-fg-38.xterm-dim { color: #00afd780; }.xterm-dom-renderer-owner-1 .xterm-bg-38 { background-color: #00afd7; }.xterm-dom-renderer-owner-1 .xterm-fg-39 { color: #00afff; }.xterm-dom-renderer-owner-1 .xterm-fg-39.xterm-dim { color: #00afff80; }.xterm-dom-renderer-owner-1 .xterm-bg-39 { background-color: #00afff; }.xterm-dom-renderer-owner-1 .xterm-fg-40 { color: #00d700; }.xterm-dom-renderer-owner-1 .xterm-fg-40.xterm-dim { color: #00d70080; }.xterm-dom-renderer-owner-1 .xterm-bg-40 { background-color: #00d700; }.xterm-dom-renderer-owner-1 .xterm-fg-41 { color: #00d75f; }.xterm-dom-renderer-owner-1 .xterm-fg-41.xterm-dim { color: #00d75f80; }.xterm-dom-renderer-owner-1 .xterm-bg-41 { background-color: #00d75f; }.xterm-dom-renderer-owner-1 .xterm-fg-42 { color: #00d787; }.xterm-dom-renderer-owner-1 .xterm-fg-42.xterm-dim { color: #00d78780; }.xterm-dom-renderer-owner-1 .xterm-bg-42 { background-color: #00d787; }.xterm-dom-renderer-owner-1 .xterm-fg-43 { color: #00d7af; }.xterm-dom-renderer-owner-1 .xterm-fg-43.xterm-dim { color: #00d7af80; }.xterm-dom-renderer-owner-1 .xterm-bg-43 { background-color: #00d7af; }.xterm-dom-renderer-owner-1 .xterm-fg-44 { color: #00d7d7; }.xterm-dom-renderer-owner-1 .xterm-fg-44.xterm-dim { color: #00d7d780; }.xterm-dom-renderer-owner-1 .xterm-bg-44 { background-color: #00d7d7; }.xterm-dom-renderer-owner-1 .xterm-fg-45 { color: #00d7ff; }.xterm-dom-renderer-owner-1 .xterm-fg-45.xterm-dim { color: #00d7ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-45 { background-color: #00d7ff; }.xterm-dom-renderer-owner-1 .xterm-fg-46 { color: #00ff00; }.xterm-dom-renderer-owner-1 .xterm-fg-46.xterm-dim { color: #00ff0080; }.xterm-dom-renderer-owner-1 .xterm-bg-46 { background-color: #00ff00; }.xterm-dom-renderer-owner-1 .xterm-fg-47 { color: #00ff5f; }.xterm-dom-renderer-owner-1 .xterm-fg-47.xterm-dim { color: #00ff5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-47 { background-color: #00ff5f; }.xterm-dom-renderer-owner-1 .xterm-fg-48 { color: #00ff87; }.xterm-dom-renderer-owner-1 .xterm-fg-48.xterm-dim { color: #00ff8780; }.xterm-dom-renderer-owner-1 .xterm-bg-48 { background-color: #00ff87; }.xterm-dom-renderer-owner-1 .xterm-fg-49 { color: #00ffaf; }.xterm-dom-renderer-owner-1 .xterm-fg-49.xterm-dim { color: #00ffaf80; }.xterm-dom-renderer-owner-1 .xterm-bg-49 { background-color: #00ffaf; }.xterm-dom-renderer-owner-1 .xterm-fg-50 { color: #00ffd7; }.xterm-dom-renderer-owner-1 .xterm-fg-50.xterm-dim { color: #00ffd780; }.xterm-dom-renderer-owner-1 .xterm-bg-50 { background-color: #00ffd7; }.xterm-dom-renderer-owner-1 .xterm-fg-51 { color: #00ffff; }.xterm-dom-renderer-owner-1 .xterm-fg-51.xterm-dim { color: #00ffff80; }.xterm-dom-renderer-owner-1 .xterm-bg-51 { background-color: #00ffff; }.xterm-dom-renderer-owner-1 .xterm-fg-52 { color: #5f0000; }.xterm-dom-renderer-owner-1 .xterm-fg-52.xterm-dim { color: #5f000080; }.xterm-dom-renderer-owner-1 .xterm-bg-52 { background-color: #5f0000; }.xterm-dom-renderer-owner-1 .xterm-fg-53 { color: #5f005f; }.xterm-dom-renderer-owner-1 .xterm-fg-53.xterm-dim { color: #5f005f80; }.xterm-dom-renderer-owner-1 .xterm-bg-53 { background-color: #5f005f; }.xterm-dom-renderer-owner-1 .xterm-fg-54 { color: #5f0087; }.xterm-dom-renderer-owner-1 .xterm-fg-54.xterm-dim { color: #5f008780; }.xterm-dom-renderer-owner-1 .xterm-bg-54 { background-color: #5f0087; }.xterm-dom-renderer-owner-1 .xterm-fg-55 { color: #5f00af; }.xterm-dom-renderer-owner-1 .xterm-fg-55.xterm-dim { color: #5f00af80; }.xterm-dom-renderer-owner-1 .xterm-bg-55 { background-color: #5f00af; }.xterm-dom-renderer-owner-1 .xterm-fg-56 { color: #5f00d7; }.xterm-dom-renderer-owner-1 .xterm-fg-56.xterm-dim { color: #5f00d780; }.xterm-dom-renderer-owner-1 .xterm-bg-56 { background-color: #5f00d7; }.xterm-dom-renderer-owner-1 .xterm-fg-57 { color: #5f00ff; }.xterm-dom-renderer-owner-1 .xterm-fg-57.xterm-dim { color: #5f00ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-57 { background-color: #5f00ff; }.xterm-dom-renderer-owner-1 .xterm-fg-58 { color: #5f5f00; }.xterm-dom-renderer-owner-1 .xterm-fg-58.xterm-dim { color: #5f5f0080; }.xterm-dom-renderer-owner-1 .xterm-bg-58 { background-color: #5f5f00; }.xterm-dom-renderer-owner-1 .xterm-fg-59 { color: #5f5f5f; }.xterm-dom-renderer-owner-1 .xterm-fg-59.xterm-dim { color: #5f5f5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-59 { background-color: #5f5f5f; }.xterm-dom-renderer-owner-1 .xterm-fg-60 { color: #5f5f87; }.xterm-dom-renderer-owner-1 .xterm-fg-60.xterm-dim { color: #5f5f8780; }.xterm-dom-renderer-owner-1 .xterm-bg-60 { background-color: #5f5f87; }.xterm-dom-renderer-owner-1 .xterm-fg-61 { color: #5f5faf; }.xterm-dom-renderer-owner-1 .xterm-fg-61.xterm-dim { color: #5f5faf80; }.xterm-dom-renderer-owner-1 .xterm-bg-61 { background-color: #5f5faf; }.xterm-dom-renderer-owner-1 .xterm-fg-62 { color: #5f5fd7; }.xterm-dom-renderer-owner-1 .xterm-fg-62.xterm-dim { color: #5f5fd780; }.xterm-dom-renderer-owner-1 .xterm-bg-62 { background-color: #5f5fd7; }.xterm-dom-renderer-owner-1 .xterm-fg-63 { color: #5f5fff; }.xterm-dom-renderer-owner-1 .xterm-fg-63.xterm-dim { color: #5f5fff80; }.xterm-dom-renderer-owner-1 .xterm-bg-63 { background-color: #5f5fff; }.xterm-dom-renderer-owner-1 .xterm-fg-64 { color: #5f8700; }.xterm-dom-renderer-owner-1 .xterm-fg-64.xterm-dim { color: #5f870080; }.xterm-dom-renderer-owner-1 .xterm-bg-64 { background-color: #5f8700; }.xterm-dom-renderer-owner-1 .xterm-fg-65 { color: #5f875f; }.xterm-dom-renderer-owner-1 .xterm-fg-65.xterm-dim { color: #5f875f80; }.xterm-dom-renderer-owner-1 .xterm-bg-65 { background-color: #5f875f; }.xterm-dom-renderer-owner-1 .xterm-fg-66 { color: #5f8787; }.xterm-dom-renderer-owner-1 .xterm-fg-66.xterm-dim { color: #5f878780; }.xterm-dom-renderer-owner-1 .xterm-bg-66 { background-color: #5f8787; }.xterm-dom-renderer-owner-1 .xterm-fg-67 { color: #5f87af; }.xterm-dom-renderer-owner-1 .xterm-fg-67.xterm-dim { color: #5f87af80; }.xterm-dom-renderer-owner-1 .xterm-bg-67 { background-color: #5f87af; }.xterm-dom-renderer-owner-1 .xterm-fg-68 { color: #5f87d7; }.xterm-dom-renderer-owner-1 .xterm-fg-68.xterm-dim { color: #5f87d780; }.xterm-dom-renderer-owner-1 .xterm-bg-68 { background-color: #5f87d7; }.xterm-dom-renderer-owner-1 .xterm-fg-69 { color: #5f87ff; }.xterm-dom-renderer-owner-1 .xterm-fg-69.xterm-dim { color: #5f87ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-69 { background-color: #5f87ff; }.xterm-dom-renderer-owner-1 .xterm-fg-70 { color: #5faf00; }.xterm-dom-renderer-owner-1 .xterm-fg-70.xterm-dim { color: #5faf0080; }.xterm-dom-renderer-owner-1 .xterm-bg-70 { background-color: #5faf00; }.xterm-dom-renderer-owner-1 .xterm-fg-71 { color: #5faf5f; }.xterm-dom-renderer-owner-1 .xterm-fg-71.xterm-dim { color: #5faf5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-71 { background-color: #5faf5f; }.xterm-dom-renderer-owner-1 .xterm-fg-72 { color: #5faf87; }.xterm-dom-renderer-owner-1 .xterm-fg-72.xterm-dim { color: #5faf8780; }.xterm-dom-renderer-owner-1 .xterm-bg-72 { background-color: #5faf87; }.xterm-dom-renderer-owner-1 .xterm-fg-73 { color: #5fafaf; }.xterm-dom-renderer-owner-1 .xterm-fg-73.xterm-dim { color: #5fafaf80; }.xterm-dom-renderer-owner-1 .xterm-bg-73 { background-color: #5fafaf; }.xterm-dom-renderer-owner-1 .xterm-fg-74 { color: #5fafd7; }.xterm-dom-renderer-owner-1 .xterm-fg-74.xterm-dim { color: #5fafd780; }.xterm-dom-renderer-owner-1 .xterm-bg-74 { background-color: #5fafd7; }.xterm-dom-renderer-owner-1 .xterm-fg-75 { color: #5fafff; }.xterm-dom-renderer-owner-1 .xterm-fg-75.xterm-dim { color: #5fafff80; }.xterm-dom-renderer-owner-1 .xterm-bg-75 { background-color: #5fafff; }.xterm-dom-renderer-owner-1 .xterm-fg-76 { color: #5fd700; }.xterm-dom-renderer-owner-1 .xterm-fg-76.xterm-dim { color: #5fd70080; }.xterm-dom-renderer-owner-1 .xterm-bg-76 { background-color: #5fd700; }.xterm-dom-renderer-owner-1 .xterm-fg-77 { color: #5fd75f; }.xterm-dom-renderer-owner-1 .xterm-fg-77.xterm-dim { color: #5fd75f80; }.xterm-dom-renderer-owner-1 .xterm-bg-77 { background-color: #5fd75f; }.xterm-dom-renderer-owner-1 .xterm-fg-78 { color: #5fd787; }.xterm-dom-renderer-owner-1 .xterm-fg-78.xterm-dim { color: #5fd78780; }.xterm-dom-renderer-owner-1 .xterm-bg-78 { background-color: #5fd787; }.xterm-dom-renderer-owner-1 .xterm-fg-79 { color: #5fd7af; }.xterm-dom-renderer-owner-1 .xterm-fg-79.xterm-dim { color: #5fd7af80; }.xterm-dom-renderer-owner-1 .xterm-bg-79 { background-color: #5fd7af; }.xterm-dom-renderer-owner-1 .xterm-fg-80 { color: #5fd7d7; }.xterm-dom-renderer-owner-1 .xterm-fg-80.xterm-dim { color: #5fd7d780; }.xterm-dom-renderer-owner-1 .xterm-bg-80 { background-color: #5fd7d7; }.xterm-dom-renderer-owner-1 .xterm-fg-81 { color: #5fd7ff; }.xterm-dom-renderer-owner-1 .xterm-fg-81.xterm-dim { color: #5fd7ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-81 { background-color: #5fd7ff; }.xterm-dom-renderer-owner-1 .xterm-fg-82 { color: #5fff00; }.xterm-dom-renderer-owner-1 .xterm-fg-82.xterm-dim { color: #5fff0080; }.xterm-dom-renderer-owner-1 .xterm-bg-82 { background-color: #5fff00; }.xterm-dom-renderer-owner-1 .xterm-fg-83 { color: #5fff5f; }.xterm-dom-renderer-owner-1 .xterm-fg-83.xterm-dim { color: #5fff5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-83 { background-color: #5fff5f; }.xterm-dom-renderer-owner-1 .xterm-fg-84 { color: #5fff87; }.xterm-dom-renderer-owner-1 .xterm-fg-84.xterm-dim { color: #5fff8780; }.xterm-dom-renderer-owner-1 .xterm-bg-84 { background-color: #5fff87; }.xterm-dom-renderer-owner-1 .xterm-fg-85 { color: #5fffaf; }.xterm-dom-renderer-owner-1 .xterm-fg-85.xterm-dim { color: #5fffaf80; }.xterm-dom-renderer-owner-1 .xterm-bg-85 { background-color: #5fffaf; }.xterm-dom-renderer-owner-1 .xterm-fg-86 { color: #5fffd7; }.xterm-dom-renderer-owner-1 .xterm-fg-86.xterm-dim { color: #5fffd780; }.xterm-dom-renderer-owner-1 .xterm-bg-86 { background-color: #5fffd7; }.xterm-dom-renderer-owner-1 .xterm-fg-87 { color: #5fffff; }.xterm-dom-renderer-owner-1 .xterm-fg-87.xterm-dim { color: #5fffff80; }.xterm-dom-renderer-owner-1 .xterm-bg-87 { background-color: #5fffff; }.xterm-dom-renderer-owner-1 .xterm-fg-88 { color: #870000; }.xterm-dom-renderer-owner-1 .xterm-fg-88.xterm-dim { color: #87000080; }.xterm-dom-renderer-owner-1 .xterm-bg-88 { background-color: #870000; }.xterm-dom-renderer-owner-1 .xterm-fg-89 { color: #87005f; }.xterm-dom-renderer-owner-1 .xterm-fg-89.xterm-dim { color: #87005f80; }.xterm-dom-renderer-owner-1 .xterm-bg-89 { background-color: #87005f; }.xterm-dom-renderer-owner-1 .xterm-fg-90 { color: #870087; }.xterm-dom-renderer-owner-1 .xterm-fg-90.xterm-dim { color: #87008780; }.xterm-dom-renderer-owner-1 .xterm-bg-90 { background-color: #870087; }.xterm-dom-renderer-owner-1 .xterm-fg-91 { color: #8700af; }.xterm-dom-renderer-owner-1 .xterm-fg-91.xterm-dim { color: #8700af80; }.xterm-dom-renderer-owner-1 .xterm-bg-91 { background-color: #8700af; }.xterm-dom-renderer-owner-1 .xterm-fg-92 { color: #8700d7; }.xterm-dom-renderer-owner-1 .xterm-fg-92.xterm-dim { color: #8700d780; }.xterm-dom-renderer-owner-1 .xterm-bg-92 { background-color: #8700d7; }.xterm-dom-renderer-owner-1 .xterm-fg-93 { color: #8700ff; }.xterm-dom-renderer-owner-1 .xterm-fg-93.xterm-dim { color: #8700ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-93 { background-color: #8700ff; }.xterm-dom-renderer-owner-1 .xterm-fg-94 { color: #875f00; }.xterm-dom-renderer-owner-1 .xterm-fg-94.xterm-dim { color: #875f0080; }.xterm-dom-renderer-owner-1 .xterm-bg-94 { background-color: #875f00; }.xterm-dom-renderer-owner-1 .xterm-fg-95 { color: #875f5f; }.xterm-dom-renderer-owner-1 .xterm-fg-95.xterm-dim { color: #875f5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-95 { background-color: #875f5f; }.xterm-dom-renderer-owner-1 .xterm-fg-96 { color: #875f87; }.xterm-dom-renderer-owner-1 .xterm-fg-96.xterm-dim { color: #875f8780; }.xterm-dom-renderer-owner-1 .xterm-bg-96 { background-color: #875f87; }.xterm-dom-renderer-owner-1 .xterm-fg-97 { color: #875faf; }.xterm-dom-renderer-owner-1 .xterm-fg-97.xterm-dim { color: #875faf80; }.xterm-dom-renderer-owner-1 .xterm-bg-97 { background-color: #875faf; }.xterm-dom-renderer-owner-1 .xterm-fg-98 { color: #875fd7; }.xterm-dom-renderer-owner-1 .xterm-fg-98.xterm-dim { color: #875fd780; }.xterm-dom-renderer-owner-1 .xterm-bg-98 { background-color: #875fd7; }.xterm-dom-renderer-owner-1 .xterm-fg-99 { color: #875fff; }.xterm-dom-renderer-owner-1 .xterm-fg-99.xterm-dim { color: #875fff80; }.xterm-dom-renderer-owner-1 .xterm-bg-99 { background-color: #875fff; }.xterm-dom-renderer-owner-1 .xterm-fg-100 { color: #878700; }.xterm-dom-renderer-owner-1 .xterm-fg-100.xterm-dim { color: #87870080; }.xterm-dom-renderer-owner-1 .xterm-bg-100 { background-color: #878700; }.xterm-dom-renderer-owner-1 .xterm-fg-101 { color: #87875f; }.xterm-dom-renderer-owner-1 .xterm-fg-101.xterm-dim { color: #87875f80; }.xterm-dom-renderer-owner-1 .xterm-bg-101 { background-color: #87875f; }.xterm-dom-renderer-owner-1 .xterm-fg-102 { color: #878787; }.xterm-dom-renderer-owner-1 .xterm-fg-102.xterm-dim { color: #87878780; }.xterm-dom-renderer-owner-1 .xterm-bg-102 { background-color: #878787; }.xterm-dom-renderer-owner-1 .xterm-fg-103 { color: #8787af; }.xterm-dom-renderer-owner-1 .xterm-fg-103.xterm-dim { color: #8787af80; }.xterm-dom-renderer-owner-1 .xterm-bg-103 { background-color: #8787af; }.xterm-dom-renderer-owner-1 .xterm-fg-104 { color: #8787d7; }.xterm-dom-renderer-owner-1 .xterm-fg-104.xterm-dim { color: #8787d780; }.xterm-dom-renderer-owner-1 .xterm-bg-104 { background-color: #8787d7; }.xterm-dom-renderer-owner-1 .xterm-fg-105 { color: #8787ff; }.xterm-dom-renderer-owner-1 .xterm-fg-105.xterm-dim { color: #8787ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-105 { background-color: #8787ff; }.xterm-dom-renderer-owner-1 .xterm-fg-106 { color: #87af00; }.xterm-dom-renderer-owner-1 .xterm-fg-106.xterm-dim { color: #87af0080; }.xterm-dom-renderer-owner-1 .xterm-bg-106 { background-color: #87af00; }.xterm-dom-renderer-owner-1 .xterm-fg-107 { color: #87af5f; }.xterm-dom-renderer-owner-1 .xterm-fg-107.xterm-dim { color: #87af5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-107 { background-color: #87af5f; }.xterm-dom-renderer-owner-1 .xterm-fg-108 { color: #87af87; }.xterm-dom-renderer-owner-1 .xterm-fg-108.xterm-dim { color: #87af8780; }.xterm-dom-renderer-owner-1 .xterm-bg-108 { background-color: #87af87; }.xterm-dom-renderer-owner-1 .xterm-fg-109 { color: #87afaf; }.xterm-dom-renderer-owner-1 .xterm-fg-109.xterm-dim { color: #87afaf80; }.xterm-dom-renderer-owner-1 .xterm-bg-109 { background-color: #87afaf; }.xterm-dom-renderer-owner-1 .xterm-fg-110 { color: #87afd7; }.xterm-dom-renderer-owner-1 .xterm-fg-110.xterm-dim { color: #87afd780; }.xterm-dom-renderer-owner-1 .xterm-bg-110 { background-color: #87afd7; }.xterm-dom-renderer-owner-1 .xterm-fg-111 { color: #87afff; }.xterm-dom-renderer-owner-1 .xterm-fg-111.xterm-dim { color: #87afff80; }.xterm-dom-renderer-owner-1 .xterm-bg-111 { background-color: #87afff; }.xterm-dom-renderer-owner-1 .xterm-fg-112 { color: #87d700; }.xterm-dom-renderer-owner-1 .xterm-fg-112.xterm-dim { color: #87d70080; }.xterm-dom-renderer-owner-1 .xterm-bg-112 { background-color: #87d700; }.xterm-dom-renderer-owner-1 .xterm-fg-113 { color: #87d75f; }.xterm-dom-renderer-owner-1 .xterm-fg-113.xterm-dim { color: #87d75f80; }.xterm-dom-renderer-owner-1 .xterm-bg-113 { background-color: #87d75f; }.xterm-dom-renderer-owner-1 .xterm-fg-114 { color: #87d787; }.xterm-dom-renderer-owner-1 .xterm-fg-114.xterm-dim { color: #87d78780; }.xterm-dom-renderer-owner-1 .xterm-bg-114 { background-color: #87d787; }.xterm-dom-renderer-owner-1 .xterm-fg-115 { color: #87d7af; }.xterm-dom-renderer-owner-1 .xterm-fg-115.xterm-dim { color: #87d7af80; }.xterm-dom-renderer-owner-1 .xterm-bg-115 { background-color: #87d7af; }.xterm-dom-renderer-owner-1 .xterm-fg-116 { color: #87d7d7; }.xterm-dom-renderer-owner-1 .xterm-fg-116.xterm-dim { color: #87d7d780; }.xterm-dom-renderer-owner-1 .xterm-bg-116 { background-color: #87d7d7; }.xterm-dom-renderer-owner-1 .xterm-fg-117 { color: #87d7ff; }.xterm-dom-renderer-owner-1 .xterm-fg-117.xterm-dim { color: #87d7ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-117 { background-color: #87d7ff; }.xterm-dom-renderer-owner-1 .xterm-fg-118 { color: #87ff00; }.xterm-dom-renderer-owner-1 .xterm-fg-118.xterm-dim { color: #87ff0080; }.xterm-dom-renderer-owner-1 .xterm-bg-118 { background-color: #87ff00; }.xterm-dom-renderer-owner-1 .xterm-fg-119 { color: #87ff5f; }.xterm-dom-renderer-owner-1 .xterm-fg-119.xterm-dim { color: #87ff5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-119 { background-color: #87ff5f; }.xterm-dom-renderer-owner-1 .xterm-fg-120 { color: #87ff87; }.xterm-dom-renderer-owner-1 .xterm-fg-120.xterm-dim { color: #87ff8780; }.xterm-dom-renderer-owner-1 .xterm-bg-120 { background-color: #87ff87; }.xterm-dom-renderer-owner-1 .xterm-fg-121 { color: #87ffaf; }.xterm-dom-renderer-owner-1 .xterm-fg-121.xterm-dim { color: #87ffaf80; }.xterm-dom-renderer-owner-1 .xterm-bg-121 { background-color: #87ffaf; }.xterm-dom-renderer-owner-1 .xterm-fg-122 { color: #87ffd7; }.xterm-dom-renderer-owner-1 .xterm-fg-122.xterm-dim { color: #87ffd780; }.xterm-dom-renderer-owner-1 .xterm-bg-122 { background-color: #87ffd7; }.xterm-dom-renderer-owner-1 .xterm-fg-123 { color: #87ffff; }.xterm-dom-renderer-owner-1 .xterm-fg-123.xterm-dim { color: #87ffff80; }.xterm-dom-renderer-owner-1 .xterm-bg-123 { background-color: #87ffff; }.xterm-dom-renderer-owner-1 .xterm-fg-124 { color: #af0000; }.xterm-dom-renderer-owner-1 .xterm-fg-124.xterm-dim { color: #af000080; }.xterm-dom-renderer-owner-1 .xterm-bg-124 { background-color: #af0000; }.xterm-dom-renderer-owner-1 .xterm-fg-125 { color: #af005f; }.xterm-dom-renderer-owner-1 .xterm-fg-125.xterm-dim { color: #af005f80; }.xterm-dom-renderer-owner-1 .xterm-bg-125 { background-color: #af005f; }.xterm-dom-renderer-owner-1 .xterm-fg-126 { color: #af0087; }.xterm-dom-renderer-owner-1 .xterm-fg-126.xterm-dim { color: #af008780; }.xterm-dom-renderer-owner-1 .xterm-bg-126 { background-color: #af0087; }.xterm-dom-renderer-owner-1 .xterm-fg-127 { color: #af00af; }.xterm-dom-renderer-owner-1 .xterm-fg-127.xterm-dim { color: #af00af80; }.xterm-dom-renderer-owner-1 .xterm-bg-127 { background-color: #af00af; }.xterm-dom-renderer-owner-1 .xterm-fg-128 { color: #af00d7; }.xterm-dom-renderer-owner-1 .xterm-fg-128.xterm-dim { color: #af00d780; }.xterm-dom-renderer-owner-1 .xterm-bg-128 { background-color: #af00d7; }.xterm-dom-renderer-owner-1 .xterm-fg-129 { color: #af00ff; }.xterm-dom-renderer-owner-1 .xterm-fg-129.xterm-dim { color: #af00ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-129 { background-color: #af00ff; }.xterm-dom-renderer-owner-1 .xterm-fg-130 { color: #af5f00; }.xterm-dom-renderer-owner-1 .xterm-fg-130.xterm-dim { color: #af5f0080; }.xterm-dom-renderer-owner-1 .xterm-bg-130 { background-color: #af5f00; }.xterm-dom-renderer-owner-1 .xterm-fg-131 { color: #af5f5f; }.xterm-dom-renderer-owner-1 .xterm-fg-131.xterm-dim { color: #af5f5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-131 { background-color: #af5f5f; }.xterm-dom-renderer-owner-1 .xterm-fg-132 { color: #af5f87; }.xterm-dom-renderer-owner-1 .xterm-fg-132.xterm-dim { color: #af5f8780; }.xterm-dom-renderer-owner-1 .xterm-bg-132 { background-color: #af5f87; }.xterm-dom-renderer-owner-1 .xterm-fg-133 { color: #af5faf; }.xterm-dom-renderer-owner-1 .xterm-fg-133.xterm-dim { color: #af5faf80; }.xterm-dom-renderer-owner-1 .xterm-bg-133 { background-color: #af5faf; }.xterm-dom-renderer-owner-1 .xterm-fg-134 { color: #af5fd7; }.xterm-dom-renderer-owner-1 .xterm-fg-134.xterm-dim { color: #af5fd780; }.xterm-dom-renderer-owner-1 .xterm-bg-134 { background-color: #af5fd7; }.xterm-dom-renderer-owner-1 .xterm-fg-135 { color: #af5fff; }.xterm-dom-renderer-owner-1 .xterm-fg-135.xterm-dim { color: #af5fff80; }.xterm-dom-renderer-owner-1 .xterm-bg-135 { background-color: #af5fff; }.xterm-dom-renderer-owner-1 .xterm-fg-136 { color: #af8700; }.xterm-dom-renderer-owner-1 .xterm-fg-136.xterm-dim { color: #af870080; }.xterm-dom-renderer-owner-1 .xterm-bg-136 { background-color: #af8700; }.xterm-dom-renderer-owner-1 .xterm-fg-137 { color: #af875f; }.xterm-dom-renderer-owner-1 .xterm-fg-137.xterm-dim { color: #af875f80; }.xterm-dom-renderer-owner-1 .xterm-bg-137 { background-color: #af875f; }.xterm-dom-renderer-owner-1 .xterm-fg-138 { color: #af8787; }.xterm-dom-renderer-owner-1 .xterm-fg-138.xterm-dim { color: #af878780; }.xterm-dom-renderer-owner-1 .xterm-bg-138 { background-color: #af8787; }.xterm-dom-renderer-owner-1 .xterm-fg-139 { color: #af87af; }.xterm-dom-renderer-owner-1 .xterm-fg-139.xterm-dim { color: #af87af80; }.xterm-dom-renderer-owner-1 .xterm-bg-139 { background-color: #af87af; }.xterm-dom-renderer-owner-1 .xterm-fg-140 { color: #af87d7; }.xterm-dom-renderer-owner-1 .xterm-fg-140.xterm-dim { color: #af87d780; }.xterm-dom-renderer-owner-1 .xterm-bg-140 { background-color: #af87d7; }.xterm-dom-renderer-owner-1 .xterm-fg-141 { color: #af87ff; }.xterm-dom-renderer-owner-1 .xterm-fg-141.xterm-dim { color: #af87ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-141 { background-color: #af87ff; }.xterm-dom-renderer-owner-1 .xterm-fg-142 { color: #afaf00; }.xterm-dom-renderer-owner-1 .xterm-fg-142.xterm-dim { color: #afaf0080; }.xterm-dom-renderer-owner-1 .xterm-bg-142 { background-color: #afaf00; }.xterm-dom-renderer-owner-1 .xterm-fg-143 { color: #afaf5f; }.xterm-dom-renderer-owner-1 .xterm-fg-143.xterm-dim { color: #afaf5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-143 { background-color: #afaf5f; }.xterm-dom-renderer-owner-1 .xterm-fg-144 { color: #afaf87; }.xterm-dom-renderer-owner-1 .xterm-fg-144.xterm-dim { color: #afaf8780; }.xterm-dom-renderer-owner-1 .xterm-bg-144 { background-color: #afaf87; }.xterm-dom-renderer-owner-1 .xterm-fg-145 { color: #afafaf; }.xterm-dom-renderer-owner-1 .xterm-fg-145.xterm-dim { color: #afafaf80; }.xterm-dom-renderer-owner-1 .xterm-bg-145 { background-color: #afafaf; }.xterm-dom-renderer-owner-1 .xterm-fg-146 { color: #afafd7; }.xterm-dom-renderer-owner-1 .xterm-fg-146.xterm-dim { color: #afafd780; }.xterm-dom-renderer-owner-1 .xterm-bg-146 { background-color: #afafd7; }.xterm-dom-renderer-owner-1 .xterm-fg-147 { color: #afafff; }.xterm-dom-renderer-owner-1 .xterm-fg-147.xterm-dim { color: #afafff80; }.xterm-dom-renderer-owner-1 .xterm-bg-147 { background-color: #afafff; }.xterm-dom-renderer-owner-1 .xterm-fg-148 { color: #afd700; }.xterm-dom-renderer-owner-1 .xterm-fg-148.xterm-dim { color: #afd70080; }.xterm-dom-renderer-owner-1 .xterm-bg-148 { background-color: #afd700; }.xterm-dom-renderer-owner-1 .xterm-fg-149 { color: #afd75f; }.xterm-dom-renderer-owner-1 .xterm-fg-149.xterm-dim { color: #afd75f80; }.xterm-dom-renderer-owner-1 .xterm-bg-149 { background-color: #afd75f; }.xterm-dom-renderer-owner-1 .xterm-fg-150 { color: #afd787; }.xterm-dom-renderer-owner-1 .xterm-fg-150.xterm-dim { color: #afd78780; }.xterm-dom-renderer-owner-1 .xterm-bg-150 { background-color: #afd787; }.xterm-dom-renderer-owner-1 .xterm-fg-151 { color: #afd7af; }.xterm-dom-renderer-owner-1 .xterm-fg-151.xterm-dim { color: #afd7af80; }.xterm-dom-renderer-owner-1 .xterm-bg-151 { background-color: #afd7af; }.xterm-dom-renderer-owner-1 .xterm-fg-152 { color: #afd7d7; }.xterm-dom-renderer-owner-1 .xterm-fg-152.xterm-dim { color: #afd7d780; }.xterm-dom-renderer-owner-1 .xterm-bg-152 { background-color: #afd7d7; }.xterm-dom-renderer-owner-1 .xterm-fg-153 { color: #afd7ff; }.xterm-dom-renderer-owner-1 .xterm-fg-153.xterm-dim { color: #afd7ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-153 { background-color: #afd7ff; }.xterm-dom-renderer-owner-1 .xterm-fg-154 { color: #afff00; }.xterm-dom-renderer-owner-1 .xterm-fg-154.xterm-dim { color: #afff0080; }.xterm-dom-renderer-owner-1 .xterm-bg-154 { background-color: #afff00; }.xterm-dom-renderer-owner-1 .xterm-fg-155 { color: #afff5f; }.xterm-dom-renderer-owner-1 .xterm-fg-155.xterm-dim { color: #afff5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-155 { background-color: #afff5f; }.xterm-dom-renderer-owner-1 .xterm-fg-156 { color: #afff87; }.xterm-dom-renderer-owner-1 .xterm-fg-156.xterm-dim { color: #afff8780; }.xterm-dom-renderer-owner-1 .xterm-bg-156 { background-color: #afff87; }.xterm-dom-renderer-owner-1 .xterm-fg-157 { color: #afffaf; }.xterm-dom-renderer-owner-1 .xterm-fg-157.xterm-dim { color: #afffaf80; }.xterm-dom-renderer-owner-1 .xterm-bg-157 { background-color: #afffaf; }.xterm-dom-renderer-owner-1 .xterm-fg-158 { color: #afffd7; }.xterm-dom-renderer-owner-1 .xterm-fg-158.xterm-dim { color: #afffd780; }.xterm-dom-renderer-owner-1 .xterm-bg-158 { background-color: #afffd7; }.xterm-dom-renderer-owner-1 .xterm-fg-159 { color: #afffff; }.xterm-dom-renderer-owner-1 .xterm-fg-159.xterm-dim { color: #afffff80; }.xterm-dom-renderer-owner-1 .xterm-bg-159 { background-color: #afffff; }.xterm-dom-renderer-owner-1 .xterm-fg-160 { color: #d70000; }.xterm-dom-renderer-owner-1 .xterm-fg-160.xterm-dim { color: #d7000080; }.xterm-dom-renderer-owner-1 .xterm-bg-160 { background-color: #d70000; }.xterm-dom-renderer-owner-1 .xterm-fg-161 { color: #d7005f; }.xterm-dom-renderer-owner-1 .xterm-fg-161.xterm-dim { color: #d7005f80; }.xterm-dom-renderer-owner-1 .xterm-bg-161 { background-color: #d7005f; }.xterm-dom-renderer-owner-1 .xterm-fg-162 { color: #d70087; }.xterm-dom-renderer-owner-1 .xterm-fg-162.xterm-dim { color: #d7008780; }.xterm-dom-renderer-owner-1 .xterm-bg-162 { background-color: #d70087; }.xterm-dom-renderer-owner-1 .xterm-fg-163 { color: #d700af; }.xterm-dom-renderer-owner-1 .xterm-fg-163.xterm-dim { color: #d700af80; }.xterm-dom-renderer-owner-1 .xterm-bg-163 { background-color: #d700af; }.xterm-dom-renderer-owner-1 .xterm-fg-164 { color: #d700d7; }.xterm-dom-renderer-owner-1 .xterm-fg-164.xterm-dim { color: #d700d780; }.xterm-dom-renderer-owner-1 .xterm-bg-164 { background-color: #d700d7; }.xterm-dom-renderer-owner-1 .xterm-fg-165 { color: #d700ff; }.xterm-dom-renderer-owner-1 .xterm-fg-165.xterm-dim { color: #d700ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-165 { background-color: #d700ff; }.xterm-dom-renderer-owner-1 .xterm-fg-166 { color: #d75f00; }.xterm-dom-renderer-owner-1 .xterm-fg-166.xterm-dim { color: #d75f0080; }.xterm-dom-renderer-owner-1 .xterm-bg-166 { background-color: #d75f00; }.xterm-dom-renderer-owner-1 .xterm-fg-167 { color: #d75f5f; }.xterm-dom-renderer-owner-1 .xterm-fg-167.xterm-dim { color: #d75f5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-167 { background-color: #d75f5f; }.xterm-dom-renderer-owner-1 .xterm-fg-168 { color: #d75f87; }.xterm-dom-renderer-owner-1 .xterm-fg-168.xterm-dim { color: #d75f8780; }.xterm-dom-renderer-owner-1 .xterm-bg-168 { background-color: #d75f87; }.xterm-dom-renderer-owner-1 .xterm-fg-169 { color: #d75faf; }.xterm-dom-renderer-owner-1 .xterm-fg-169.xterm-dim { color: #d75faf80; }.xterm-dom-renderer-owner-1 .xterm-bg-169 { background-color: #d75faf; }.xterm-dom-renderer-owner-1 .xterm-fg-170 { color: #d75fd7; }.xterm-dom-renderer-owner-1 .xterm-fg-170.xterm-dim { color: #d75fd780; }.xterm-dom-renderer-owner-1 .xterm-bg-170 { background-color: #d75fd7; }.xterm-dom-renderer-owner-1 .xterm-fg-171 { color: #d75fff; }.xterm-dom-renderer-owner-1 .xterm-fg-171.xterm-dim { color: #d75fff80; }.xterm-dom-renderer-owner-1 .xterm-bg-171 { background-color: #d75fff; }.xterm-dom-renderer-owner-1 .xterm-fg-172 { color: #d78700; }.xterm-dom-renderer-owner-1 .xterm-fg-172.xterm-dim { color: #d7870080; }.xterm-dom-renderer-owner-1 .xterm-bg-172 { background-color: #d78700; }.xterm-dom-renderer-owner-1 .xterm-fg-173 { color: #d7875f; }.xterm-dom-renderer-owner-1 .xterm-fg-173.xterm-dim { color: #d7875f80; }.xterm-dom-renderer-owner-1 .xterm-bg-173 { background-color: #d7875f; }.xterm-dom-renderer-owner-1 .xterm-fg-174 { color: #d78787; }.xterm-dom-renderer-owner-1 .xterm-fg-174.xterm-dim { color: #d7878780; }.xterm-dom-renderer-owner-1 .xterm-bg-174 { background-color: #d78787; }.xterm-dom-renderer-owner-1 .xterm-fg-175 { color: #d787af; }.xterm-dom-renderer-owner-1 .xterm-fg-175.xterm-dim { color: #d787af80; }.xterm-dom-renderer-owner-1 .xterm-bg-175 { background-color: #d787af; }.xterm-dom-renderer-owner-1 .xterm-fg-176 { color: #d787d7; }.xterm-dom-renderer-owner-1 .xterm-fg-176.xterm-dim { color: #d787d780; }.xterm-dom-renderer-owner-1 .xterm-bg-176 { background-color: #d787d7; }.xterm-dom-renderer-owner-1 .xterm-fg-177 { color: #d787ff; }.xterm-dom-renderer-owner-1 .xterm-fg-177.xterm-dim { color: #d787ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-177 { background-color: #d787ff; }.xterm-dom-renderer-owner-1 .xterm-fg-178 { color: #d7af00; }.xterm-dom-renderer-owner-1 .xterm-fg-178.xterm-dim { color: #d7af0080; }.xterm-dom-renderer-owner-1 .xterm-bg-178 { background-color: #d7af00; }.xterm-dom-renderer-owner-1 .xterm-fg-179 { color: #d7af5f; }.xterm-dom-renderer-owner-1 .xterm-fg-179.xterm-dim { color: #d7af5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-179 { background-color: #d7af5f; }.xterm-dom-renderer-owner-1 .xterm-fg-180 { color: #d7af87; }.xterm-dom-renderer-owner-1 .xterm-fg-180.xterm-dim { color: #d7af8780; }.xterm-dom-renderer-owner-1 .xterm-bg-180 { background-color: #d7af87; }.xterm-dom-renderer-owner-1 .xterm-fg-181 { color: #d7afaf; }.xterm-dom-renderer-owner-1 .xterm-fg-181.xterm-dim { color: #d7afaf80; }.xterm-dom-renderer-owner-1 .xterm-bg-181 { background-color: #d7afaf; }.xterm-dom-renderer-owner-1 .xterm-fg-182 { color: #d7afd7; }.xterm-dom-renderer-owner-1 .xterm-fg-182.xterm-dim { color: #d7afd780; }.xterm-dom-renderer-owner-1 .xterm-bg-182 { background-color: #d7afd7; }.xterm-dom-renderer-owner-1 .xterm-fg-183 { color: #d7afff; }.xterm-dom-renderer-owner-1 .xterm-fg-183.xterm-dim { color: #d7afff80; }.xterm-dom-renderer-owner-1 .xterm-bg-183 { background-color: #d7afff; }.xterm-dom-renderer-owner-1 .xterm-fg-184 { color: #d7d700; }.xterm-dom-renderer-owner-1 .xterm-fg-184.xterm-dim { color: #d7d70080; }.xterm-dom-renderer-owner-1 .xterm-bg-184 { background-color: #d7d700; }.xterm-dom-renderer-owner-1 .xterm-fg-185 { color: #d7d75f; }.xterm-dom-renderer-owner-1 .xterm-fg-185.xterm-dim { color: #d7d75f80; }.xterm-dom-renderer-owner-1 .xterm-bg-185 { background-color: #d7d75f; }.xterm-dom-renderer-owner-1 .xterm-fg-186 { color: #d7d787; }.xterm-dom-renderer-owner-1 .xterm-fg-186.xterm-dim { color: #d7d78780; }.xterm-dom-renderer-owner-1 .xterm-bg-186 { background-color: #d7d787; }.xterm-dom-renderer-owner-1 .xterm-fg-187 { color: #d7d7af; }.xterm-dom-renderer-owner-1 .xterm-fg-187.xterm-dim { color: #d7d7af80; }.xterm-dom-renderer-owner-1 .xterm-bg-187 { background-color: #d7d7af; }.xterm-dom-renderer-owner-1 .xterm-fg-188 { color: #d7d7d7; }.xterm-dom-renderer-owner-1 .xterm-fg-188.xterm-dim { color: #d7d7d780; }.xterm-dom-renderer-owner-1 .xterm-bg-188 { background-color: #d7d7d7; }.xterm-dom-renderer-owner-1 .xterm-fg-189 { color: #d7d7ff; }.xterm-dom-renderer-owner-1 .xterm-fg-189.xterm-dim { color: #d7d7ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-189 { background-color: #d7d7ff; }.xterm-dom-renderer-owner-1 .xterm-fg-190 { color: #d7ff00; }.xterm-dom-renderer-owner-1 .xterm-fg-190.xterm-dim { color: #d7ff0080; }.xterm-dom-renderer-owner-1 .xterm-bg-190 { background-color: #d7ff00; }.xterm-dom-renderer-owner-1 .xterm-fg-191 { color: #d7ff5f; }.xterm-dom-renderer-owner-1 .xterm-fg-191.xterm-dim { color: #d7ff5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-191 { background-color: #d7ff5f; }.xterm-dom-renderer-owner-1 .xterm-fg-192 { color: #d7ff87; }.xterm-dom-renderer-owner-1 .xterm-fg-192.xterm-dim { color: #d7ff8780; }.xterm-dom-renderer-owner-1 .xterm-bg-192 { background-color: #d7ff87; }.xterm-dom-renderer-owner-1 .xterm-fg-193 { color: #d7ffaf; }.xterm-dom-renderer-owner-1 .xterm-fg-193.xterm-dim { color: #d7ffaf80; }.xterm-dom-renderer-owner-1 .xterm-bg-193 { background-color: #d7ffaf; }.xterm-dom-renderer-owner-1 .xterm-fg-194 { color: #d7ffd7; }.xterm-dom-renderer-owner-1 .xterm-fg-194.xterm-dim { color: #d7ffd780; }.xterm-dom-renderer-owner-1 .xterm-bg-194 { background-color: #d7ffd7; }.xterm-dom-renderer-owner-1 .xterm-fg-195 { color: #d7ffff; }.xterm-dom-renderer-owner-1 .xterm-fg-195.xterm-dim { color: #d7ffff80; }.xterm-dom-renderer-owner-1 .xterm-bg-195 { background-color: #d7ffff; }.xterm-dom-renderer-owner-1 .xterm-fg-196 { color: #ff0000; }.xterm-dom-renderer-owner-1 .xterm-fg-196.xterm-dim { color: #ff000080; }.xterm-dom-renderer-owner-1 .xterm-bg-196 { background-color: #ff0000; }.xterm-dom-renderer-owner-1 .xterm-fg-197 { color: #ff005f; }.xterm-dom-renderer-owner-1 .xterm-fg-197.xterm-dim { color: #ff005f80; }.xterm-dom-renderer-owner-1 .xterm-bg-197 { background-color: #ff005f; }.xterm-dom-renderer-owner-1 .xterm-fg-198 { color: #ff0087; }.xterm-dom-renderer-owner-1 .xterm-fg-198.xterm-dim { color: #ff008780; }.xterm-dom-renderer-owner-1 .xterm-bg-198 { background-color: #ff0087; }.xterm-dom-renderer-owner-1 .xterm-fg-199 { color: #ff00af; }.xterm-dom-renderer-owner-1 .xterm-fg-199.xterm-dim { color: #ff00af80; }.xterm-dom-renderer-owner-1 .xterm-bg-199 { background-color: #ff00af; }.xterm-dom-renderer-owner-1 .xterm-fg-200 { color: #ff00d7; }.xterm-dom-renderer-owner-1 .xterm-fg-200.xterm-dim { color: #ff00d780; }.xterm-dom-renderer-owner-1 .xterm-bg-200 { background-color: #ff00d7; }.xterm-dom-renderer-owner-1 .xterm-fg-201 { color: #ff00ff; }.xterm-dom-renderer-owner-1 .xterm-fg-201.xterm-dim { color: #ff00ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-201 { background-color: #ff00ff; }.xterm-dom-renderer-owner-1 .xterm-fg-202 { color: #ff5f00; }.xterm-dom-renderer-owner-1 .xterm-fg-202.xterm-dim { color: #ff5f0080; }.xterm-dom-renderer-owner-1 .xterm-bg-202 { background-color: #ff5f00; }.xterm-dom-renderer-owner-1 .xterm-fg-203 { color: #ff5f5f; }.xterm-dom-renderer-owner-1 .xterm-fg-203.xterm-dim { color: #ff5f5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-203 { background-color: #ff5f5f; }.xterm-dom-renderer-owner-1 .xterm-fg-204 { color: #ff5f87; }.xterm-dom-renderer-owner-1 .xterm-fg-204.xterm-dim { color: #ff5f8780; }.xterm-dom-renderer-owner-1 .xterm-bg-204 { background-color: #ff5f87; }.xterm-dom-renderer-owner-1 .xterm-fg-205 { color: #ff5faf; }.xterm-dom-renderer-owner-1 .xterm-fg-205.xterm-dim { color: #ff5faf80; }.xterm-dom-renderer-owner-1 .xterm-bg-205 { background-color: #ff5faf; }.xterm-dom-renderer-owner-1 .xterm-fg-206 { color: #ff5fd7; }.xterm-dom-renderer-owner-1 .xterm-fg-206.xterm-dim { color: #ff5fd780; }.xterm-dom-renderer-owner-1 .xterm-bg-206 { background-color: #ff5fd7; }.xterm-dom-renderer-owner-1 .xterm-fg-207 { color: #ff5fff; }.xterm-dom-renderer-owner-1 .xterm-fg-207.xterm-dim { color: #ff5fff80; }.xterm-dom-renderer-owner-1 .xterm-bg-207 { background-color: #ff5fff; }.xterm-dom-renderer-owner-1 .xterm-fg-208 { color: #ff8700; }.xterm-dom-renderer-owner-1 .xterm-fg-208.xterm-dim { color: #ff870080; }.xterm-dom-renderer-owner-1 .xterm-bg-208 { background-color: #ff8700; }.xterm-dom-renderer-owner-1 .xterm-fg-209 { color: #ff875f; }.xterm-dom-renderer-owner-1 .xterm-fg-209.xterm-dim { color: #ff875f80; }.xterm-dom-renderer-owner-1 .xterm-bg-209 { background-color: #ff875f; }.xterm-dom-renderer-owner-1 .xterm-fg-210 { color: #ff8787; }.xterm-dom-renderer-owner-1 .xterm-fg-210.xterm-dim { color: #ff878780; }.xterm-dom-renderer-owner-1 .xterm-bg-210 { background-color: #ff8787; }.xterm-dom-renderer-owner-1 .xterm-fg-211 { color: #ff87af; }.xterm-dom-renderer-owner-1 .xterm-fg-211.xterm-dim { color: #ff87af80; }.xterm-dom-renderer-owner-1 .xterm-bg-211 { background-color: #ff87af; }.xterm-dom-renderer-owner-1 .xterm-fg-212 { color: #ff87d7; }.xterm-dom-renderer-owner-1 .xterm-fg-212.xterm-dim { color: #ff87d780; }.xterm-dom-renderer-owner-1 .xterm-bg-212 { background-color: #ff87d7; }.xterm-dom-renderer-owner-1 .xterm-fg-213 { color: #ff87ff; }.xterm-dom-renderer-owner-1 .xterm-fg-213.xterm-dim { color: #ff87ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-213 { background-color: #ff87ff; }.xterm-dom-renderer-owner-1 .xterm-fg-214 { color: #ffaf00; }.xterm-dom-renderer-owner-1 .xterm-fg-214.xterm-dim { color: #ffaf0080; }.xterm-dom-renderer-owner-1 .xterm-bg-214 { background-color: #ffaf00; }.xterm-dom-renderer-owner-1 .xterm-fg-215 { color: #ffaf5f; }.xterm-dom-renderer-owner-1 .xterm-fg-215.xterm-dim { color: #ffaf5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-215 { background-color: #ffaf5f; }.xterm-dom-renderer-owner-1 .xterm-fg-216 { color: #ffaf87; }.xterm-dom-renderer-owner-1 .xterm-fg-216.xterm-dim { color: #ffaf8780; }.xterm-dom-renderer-owner-1 .xterm-bg-216 { background-color: #ffaf87; }.xterm-dom-renderer-owner-1 .xterm-fg-217 { color: #ffafaf; }.xterm-dom-renderer-owner-1 .xterm-fg-217.xterm-dim { color: #ffafaf80; }.xterm-dom-renderer-owner-1 .xterm-bg-217 { background-color: #ffafaf; }.xterm-dom-renderer-owner-1 .xterm-fg-218 { color: #ffafd7; }.xterm-dom-renderer-owner-1 .xterm-fg-218.xterm-dim { color: #ffafd780; }.xterm-dom-renderer-owner-1 .xterm-bg-218 { background-color: #ffafd7; }.xterm-dom-renderer-owner-1 .xterm-fg-219 { color: #ffafff; }.xterm-dom-renderer-owner-1 .xterm-fg-219.xterm-dim { color: #ffafff80; }.xterm-dom-renderer-owner-1 .xterm-bg-219 { background-color: #ffafff; }.xterm-dom-renderer-owner-1 .xterm-fg-220 { color: #ffd700; }.xterm-dom-renderer-owner-1 .xterm-fg-220.xterm-dim { color: #ffd70080; }.xterm-dom-renderer-owner-1 .xterm-bg-220 { background-color: #ffd700; }.xterm-dom-renderer-owner-1 .xterm-fg-221 { color: #ffd75f; }.xterm-dom-renderer-owner-1 .xterm-fg-221.xterm-dim { color: #ffd75f80; }.xterm-dom-renderer-owner-1 .xterm-bg-221 { background-color: #ffd75f; }.xterm-dom-renderer-owner-1 .xterm-fg-222 { color: #ffd787; }.xterm-dom-renderer-owner-1 .xterm-fg-222.xterm-dim { color: #ffd78780; }.xterm-dom-renderer-owner-1 .xterm-bg-222 { background-color: #ffd787; }.xterm-dom-renderer-owner-1 .xterm-fg-223 { color: #ffd7af; }.xterm-dom-renderer-owner-1 .xterm-fg-223.xterm-dim { color: #ffd7af80; }.xterm-dom-renderer-owner-1 .xterm-bg-223 { background-color: #ffd7af; }.xterm-dom-renderer-owner-1 .xterm-fg-224 { color: #ffd7d7; }.xterm-dom-renderer-owner-1 .xterm-fg-224.xterm-dim { color: #ffd7d780; }.xterm-dom-renderer-owner-1 .xterm-bg-224 { background-color: #ffd7d7; }.xterm-dom-renderer-owner-1 .xterm-fg-225 { color: #ffd7ff; }.xterm-dom-renderer-owner-1 .xterm-fg-225.xterm-dim { color: #ffd7ff80; }.xterm-dom-renderer-owner-1 .xterm-bg-225 { background-color: #ffd7ff; }.xterm-dom-renderer-owner-1 .xterm-fg-226 { color: #ffff00; }.xterm-dom-renderer-owner-1 .xterm-fg-226.xterm-dim { color: #ffff0080; }.xterm-dom-renderer-owner-1 .xterm-bg-226 { background-color: #ffff00; }.xterm-dom-renderer-owner-1 .xterm-fg-227 { color: #ffff5f; }.xterm-dom-renderer-owner-1 .xterm-fg-227.xterm-dim { color: #ffff5f80; }.xterm-dom-renderer-owner-1 .xterm-bg-227 { background-color: #ffff5f; }.xterm-dom-renderer-owner-1 .xterm-fg-228 { color: #ffff87; }.xterm-dom-renderer-owner-1 .xterm-fg-228.xterm-dim { color: #ffff8780; }.xterm-dom-renderer-owner-1 .xterm-bg-228 { background-color: #ffff87; }.xterm-dom-renderer-owner-1 .xterm-fg-229 { color: #ffffaf; }.xterm-dom-renderer-owner-1 .xterm-fg-229.xterm-dim { color: #ffffaf80; }.xterm-dom-renderer-owner-1 .xterm-bg-229 { background-color: #ffffaf; }.xterm-dom-renderer-owner-1 .xterm-fg-230 { color: #ffffd7; }.xterm-dom-renderer-owner-1 .xterm-fg-230.xterm-dim { color: #ffffd780; }.xterm-dom-renderer-owner-1 .xterm-bg-230 { background-color: #ffffd7; }.xterm-dom-renderer-owner-1 .xterm-fg-231 { color: #ffffff; }.xterm-dom-renderer-owner-1 .xterm-fg-231.xterm-dim { color: #ffffff80; }.xterm-dom-renderer-owner-1 .xterm-bg-231 { background-color: #ffffff; }.xterm-dom-renderer-owner-1 .xterm-fg-232 { color: #080808; }.xterm-dom-renderer-owner-1 .xterm-fg-232.xterm-dim { color: #08080880; }.xterm-dom-renderer-owner-1 .xterm-bg-232 { background-color: #080808; }.xterm-dom-renderer-owner-1 .xterm-fg-233 { color: #121212; }.xterm-dom-renderer-owner-1 .xterm-fg-233.xterm-dim { color: #12121280; }.xterm-dom-renderer-owner-1 .xterm-bg-233 { background-color: #121212; }.xterm-dom-renderer-owner-1 .xterm-fg-234 { color: #1c1c1c; }.xterm-dom-renderer-owner-1 .xterm-fg-234.xterm-dim { color: #1c1c1c80; }.xterm-dom-renderer-owner-1 .xterm-bg-234 { background-color: #1c1c1c; }.xterm-dom-renderer-owner-1 .xterm-fg-235 { color: #262626; }.xterm-dom-renderer-owner-1 .xterm-fg-235.xterm-dim { color: #26262680; }.xterm-dom-renderer-owner-1 .xterm-bg-235 { background-color: #262626; }.xterm-dom-renderer-owner-1 .xterm-fg-236 { color: #303030; }.xterm-dom-renderer-owner-1 .xterm-fg-236.xterm-dim { color: #30303080; }.xterm-dom-renderer-owner-1 .xterm-bg-236 { background-color: #303030; }.xterm-dom-renderer-owner-1 .xterm-fg-237 { color: #3a3a3a; }.xterm-dom-renderer-owner-1 .xterm-fg-237.xterm-dim { color: #3a3a3a80; }.xterm-dom-renderer-owner-1 .xterm-bg-237 { background-color: #3a3a3a; }.xterm-dom-renderer-owner-1 .xterm-fg-238 { color: #444444; }.xterm-dom-renderer-owner-1 .xterm-fg-238.xterm-dim { color: #44444480; }.xterm-dom-renderer-owner-1 .xterm-bg-238 { background-color: #444444; }.xterm-dom-renderer-owner-1 .xterm-fg-239 { color: #4e4e4e; }.xterm-dom-renderer-owner-1 .xterm-fg-239.xterm-dim { color: #4e4e4e80; }.xterm-dom-renderer-owner-1 .xterm-bg-239 { background-color: #4e4e4e; }.xterm-dom-renderer-owner-1 .xterm-fg-240 { color: #585858; }.xterm-dom-renderer-owner-1 .xterm-fg-240.xterm-dim { color: #58585880; }.xterm-dom-renderer-owner-1 .xterm-bg-240 { background-color: #585858; }.xterm-dom-renderer-owner-1 .xterm-fg-241 { color: #626262; }.xterm-dom-renderer-owner-1 .xterm-fg-241.xterm-dim { color: #62626280; }.xterm-dom-renderer-owner-1 .xterm-bg-241 { background-color: #626262; }.xterm-dom-renderer-owner-1 .xterm-fg-242 { color: #6c6c6c; }.xterm-dom-renderer-owner-1 .xterm-fg-242.xterm-dim { color: #6c6c6c80; }.xterm-dom-renderer-owner-1 .xterm-bg-242 { background-color: #6c6c6c; }.xterm-dom-renderer-owner-1 .xterm-fg-243 { color: #767676; }.xterm-dom-renderer-owner-1 .xterm-fg-243.xterm-dim { color: #76767680; }.xterm-dom-renderer-owner-1 .xterm-bg-243 { background-color: #767676; }.xterm-dom-renderer-owner-1 .xterm-fg-244 { color: #808080; }.xterm-dom-renderer-owner-1 .xterm-fg-244.xterm-dim { color: #80808080; }.xterm-dom-renderer-owner-1 .xterm-bg-244 { background-color: #808080; }.xterm-dom-renderer-owner-1 .xterm-fg-245 { color: #8a8a8a; }.xterm-dom-renderer-owner-1 .xterm-fg-245.xterm-dim { color: #8a8a8a80; }.xterm-dom-renderer-owner-1 .xterm-bg-245 { background-color: #8a8a8a; }.xterm-dom-renderer-owner-1 .xterm-fg-246 { color: #949494; }.xterm-dom-renderer-owner-1 .xterm-fg-246.xterm-dim { color: #94949480; }.xterm-dom-renderer-owner-1 .xterm-bg-246 { background-color: #949494; }.xterm-dom-renderer-owner-1 .xterm-fg-247 { color: #9e9e9e; }.xterm-dom-renderer-owner-1 .xterm-fg-247.xterm-dim { color: #9e9e9e80; }.xterm-dom-renderer-owner-1 .xterm-bg-247 { background-color: #9e9e9e; }.xterm-dom-renderer-owner-1 .xterm-fg-248 { color: #a8a8a8; }.xterm-dom-renderer-owner-1 .xterm-fg-248.xterm-dim { color: #a8a8a880; }.xterm-dom-renderer-owner-1 .xterm-bg-248 { background-color: #a8a8a8; }.xterm-dom-renderer-owner-1 .xterm-fg-249 { color: #b2b2b2; }.xterm-dom-renderer-owner-1 .xterm-fg-249.xterm-dim { color: #b2b2b280; }.xterm-dom-renderer-owner-1 .xterm-bg-249 { background-color: #b2b2b2; }.xterm-dom-renderer-owner-1 .xterm-fg-250 { color: #bcbcbc; }.xterm-dom-renderer-owner-1 .xterm-fg-250.xterm-dim { color: #bcbcbc80; }.xterm-dom-renderer-owner-1 .xterm-bg-250 { background-color: #bcbcbc; }.xterm-dom-renderer-owner-1 .xterm-fg-251 { color: #c6c6c6; }.xterm-dom-renderer-owner-1 .xterm-fg-251.xterm-dim { color: #c6c6c680; }.xterm-dom-renderer-owner-1 .xterm-bg-251 { background-color: #c6c6c6; }.xterm-dom-renderer-owner-1 .xterm-fg-252 { color: #d0d0d0; }.xterm-dom-renderer-owner-1 .xterm-fg-252.xterm-dim { color: #d0d0d080; }.xterm-dom-renderer-owner-1 .xterm-bg-252 { background-color: #d0d0d0; }.xterm-dom-renderer-owner-1 .xterm-fg-253 { color: #dadada; }.xterm-dom-renderer-owner-1 .xterm-fg-253.xterm-dim { color: #dadada80; }.xterm-dom-renderer-owner-1 .xterm-bg-253 { background-color: #dadada; }.xterm-dom-renderer-owner-1 .xterm-fg-254 { color: #e4e4e4; }.xterm-dom-renderer-owner-1 .xterm-fg-254.xterm-dim { color: #e4e4e480; }.xterm-dom-renderer-owner-1 .xterm-bg-254 { background-color: #e4e4e4; }.xterm-dom-renderer-owner-1 .xterm-fg-255 { color: #eeeeee; }.xterm-dom-renderer-owner-1 .xterm-fg-255.xterm-dim { color: #eeeeee80; }.xterm-dom-renderer-owner-1 .xterm-bg-255 { background-color: #eeeeee; }.xterm-dom-renderer-owner-1 .xterm-fg-257 { color: #1e1e1e; }.xterm-dom-renderer-owner-1 .xterm-fg-257.xterm-dim { color: #1e1e1e80; }.xterm-dom-renderer-owner-1 .xterm-bg-257 { background-color: #ffffff; }</style><div class="xterm-rows" style="line-height: normal; letter-spacing: 0.0120516px;" aria-hidden="true"><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>****************************</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>stack=2</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>****************************</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>---------------------</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>Pre-reduction</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>---------------------</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>        Buffer:</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>         |||  2080 , 6176 , 10272 , 14368 , 18464 , 22560 , 26656 , 30752 , |||  34848 , 38944 , 43040 , 47136 , 51232 , 55328 , 59424 , 63520 , ||| </span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>Auxillary Buffer:</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>         2080 , 100 , 392 , 228 , 1552 , 356 , 904 , 484 , 6176 , 612 , 1416 , 740 , 3600 , 868 , 1928 , 996 ,</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>---------------------</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>Post-reduction</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>---------------------</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>        Buffer:</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>         |||  131328 , 6176 , 24640 , 14368 , 98432 , 22560 , 57408 , 30752 , |||  393472 , 38944 , 90176 , 47136 , 229504 , 55328 , 122944 , 63520 , ||| </span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>Auxillary Buffer:</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>         131328 , 393472 , 392 , 228 , 1552 , 356 , 904 , 484 , 6176 , 612 , 1416 , 740 , 3600 , 868 , 1928 , 996 ,</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>****************************</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>stack=3</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>****************************</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>---------------------</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>Pre-reduction</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>---------------------</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>        Buffer:</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>         |||  131328 , 393472 , ||| </span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>Auxillary Buffer:</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>         131328 , 6176 ,</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>---------------------</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>Post-reduction</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>---------------------</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>        Buffer:</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>         |||  524800 , 393472 , ||| </span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>Auxillary Buffer:</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>         524800 , 6176 ,</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>The computed sum is: 524800</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>GPU Execution Time: 16.70 microseconds</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span>Exit status: 0</span></div><div style="width: 1717px; height: 26px; line-height: 26px; overflow: hidden;"><span class="xterm-cursor xterm-cursor-outline"> </span></div></div><div class="xterm-selection" aria-hidden="true"><div style="height: 26px; top: 0px; left: 100.094px; width: 0px;"></div><div style="top: 26px; left: 0px; width: 1717px;"></div></div><div class="xterm-decoration-container"></div></div></div></div></div></div></div></div></div><div class="h-2"></div></div></div></div><div id="modal-root"></div><script defer="defer" src="reduction_files/vcd15cbe7772f49c399c6a5babf22c1241717689176015" integrity="sha512-ZpsOmlRQV6y907TI0dKBHq9Md29nnaEIPlkf84rnaERnq6zvWvPUqr2ft8M1aS28oN72PdrCzSjY4U6VaAw1EQ==" data-cf-beacon="{&quot;rayId&quot;:&quot;911b00731eb7cfb4&quot;,&quot;version&quot;:&quot;2025.1.0&quot;,&quot;r&quot;:1,&quot;token&quot;:&quot;ef34bbc45a4146aa81eca977f9c48ad9&quot;,&quot;serverTiming&quot;:{&quot;name&quot;:{&quot;cfExtPri&quot;:true,&quot;cfL4&quot;:true,&quot;cfSpeedBrain&quot;:true,&quot;cfCacheStatus&quot;:true}}}" crossorigin="anonymous"></script>
<script src="reduction_files/loader.js"></script><div class="monaco-aria-container"><div class="monaco-alert" role="alert" aria-atomic="true"></div><div class="monaco-alert" role="alert" aria-atomic="true"></div><div class="monaco-status" aria-live="polite" aria-atomic="true"></div><div class="monaco-status" aria-live="polite" aria-atomic="true"></div></div></body></html>
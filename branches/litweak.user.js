// ==UserScript==
// @name           LiTweak
// @namespace      lmab
// @description    LiTweak
// @include        http://www.liveinternet.ru/*
// ==/UserScript==

var s=document.createElement("li");
s.innerHTML="<a class="gl_Top-nav-menu-item-lnk\"  href=\"http://www.liveinternet.ru/journal_settings.php\">Settings</a>";

var attr = document.createAttribute('class');
attr.nodeValue = "gl_Top-nav-menu-item";
s.setAttributeNode(attr);

var el = document.getElementsByClassName("gl_Top-nav-menu");
el[0].appendChild(s);
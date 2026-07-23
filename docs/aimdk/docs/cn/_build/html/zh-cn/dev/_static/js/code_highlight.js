document.addEventListener("DOMContentLoaded", function () {
  var HL_CLASS = "code-word-highlight";
  var COPY_CLASS = "code-copy-btn";

  var style = document.createElement("style");
  style.textContent =
    "." + HL_CLASS + " { background-color: rgba(255,213,79,0.4); border-radius: 2px; }\n" +
    "div.highlight { position: relative; }\n" +
    "." + COPY_CLASS + " { position: absolute; top: 4px; right: 4px; padding: 3px 6px; " +
      "font-size: 1em; cursor: pointer; background: rgba(200,200,200,0.3); border: 1px solid rgba(150,150,150,0.4); " +
      "border-radius: 4px; opacity: 0; transition: opacity 0.2s; user-select: none; z-index: 1; }\n" +
    "div.highlight:hover ." + COPY_CLASS + " { opacity: 1; }\n" +
    "." + COPY_CLASS + ":hover { background: rgba(200,200,200,0.6); }\n" +
    "." + COPY_CLASS + ".copied { background: rgba(76,175,80,0.3); border-color: rgba(76,175,80,0.5); }";
  document.head.appendChild(style);

  var SELECTOR = "div.highlight-python > div.highlight, div.highlight-default > div.highlight";

  document.querySelectorAll(SELECTOR).forEach(function (block) {
    var btn = document.createElement("button");
    btn.className = COPY_CLASS;
    btn.textContent = "\uf0c5";
    btn.style.fontFamily = "'Font Awesome 7 Free'";
    btn.title = "Copy";
    btn.addEventListener("click", function () {
      var pre = block.querySelector("pre");
      if (!pre) return;
      var text = pre.textContent;
      navigator.clipboard.writeText(text).then(function () {
        btn.style.fontWeight = 900;
        setTimeout(function () {
          btn.textContent = "\uf0c5";
          btn.style.fontWeight = 400;
        }, 800);
      });
    });
    block.appendChild(btn);
  });

  document.addEventListener("dblclick", function (e) {
    var pre = e.target.closest("div.highlight pre");
    if (!pre || !pre.closest(".highlight-python, .highlight-default")) {
      clearHighlights();
      return;
    }

    var sel = window.getSelection();
    var word = sel ? sel.toString().trim() : "";
    if (!word || !/^[A-Za-z_]\w*$/.test(word)) {
      clearHighlights();
      return;
    }

    clearHighlights();

    var re = new RegExp("(?<![\\w])(" + word + ")(?![\\w])", "g");

    var walker = document.createTreeWalker(pre, NodeFilter.SHOW_TEXT, null);
    var textNode;
    var nodesToProcess = [];
    while ((textNode = walker.nextNode())) {
      if (re.test(textNode.nodeValue)) {
        nodesToProcess.push(textNode);
      }
      re.lastIndex = 0;
    }

    nodesToProcess.forEach(function (node) {
      var parts = node.nodeValue.split(re);
      if (parts.length <= 1) return;
      var frag = document.createDocumentFragment();
      parts.forEach(function (part) {
        if (part === word) {
          var mark = document.createElement("mark");
          mark.className = HL_CLASS;
          mark.textContent = part;
          frag.appendChild(mark);
        } else if (part) {
          frag.appendChild(document.createTextNode(part));
        }
      });
      node.parentNode.replaceChild(frag, node);
    });
  });

  function clearHighlights() {
    var marks = document.querySelectorAll("." + HL_CLASS);
    marks.forEach(function (mark) {
      var parent = mark.parentNode;
      parent.replaceChild(document.createTextNode(mark.textContent), mark);
      parent.normalize();
    });
  }
});

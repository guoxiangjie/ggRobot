selector_to_html = {"a[href=\"#id1\"]": "<h1 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">5.1.5 </span>\u7075\u521b\u52a8\u4f5c<a class=\"headerlink\" href=\"#id1\" title=\"Link to this heading\">\uf0c1</a></h1><p><strong>\u7075\u521b\u52a8\u4f5c\u63a5\u53e3\u7528\u4e8e\u83b7\u53d6\u673a\u5668\u4eba\u4e0a\u5df2\u90e8\u7f72\u7684\u7075\u521b\u52a8\u4f5c\u8d44\u6e90\u5217\u8868\uff0c\u5e76\u89e6\u53d1\u64ad\u653e\u6307\u5b9a\u7684\u52a8\u4f5c\u3002</strong></p>", "a[href=\"#id3\"]": "<h2 class=\"tippy-header\" style=\"margin-top: 0;\">\u7f16\u7a0b\u793a\u4f8b<a class=\"headerlink\" href=\"#id3\" title=\"Link to this heading\">\uf0c1</a></h2><p>\u8be6\u7ec6\u7684\u7f16\u7a0b\u793a\u4f8b\u548c\u4ee3\u7801\u8bf4\u660e\u8bf7\u53c2\u8003\uff1a</p>", "a[href=\"../../example/Python.html#py-play-linkcraft-action\"]": "<h2 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">6.1.29 </span>\u64ad\u653e\u7075\u521b\u52a8\u4f5c<a class=\"headerlink\" href=\"#py-play-linkcraft-action\" title=\"Link to this heading\">\uf0c1</a></h2><p><strong>\u8be5\u793a\u4f8b\u4e2d\u7528\u5230\u4e86play_linkcraft</strong>\uff0c\u5217\u51fa\u673a\u5668\u4eba\u4e0a\u7684\u7075\u521b\u52a8\u4f5c\uff0c\u5e76\u4e14\u9009\u62e9\u4e00\u6761\u8fdb\u884c\u64ad\u653e</p>", "a[href=\"../../example/Cpp.html#cpp-play-linkcraft-action\"]": "<h2 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">6.2.27 </span>\u64ad\u653e\u7075\u521b\u52a8\u4f5c<a class=\"headerlink\" href=\"#cpp-play-linkcraft-action\" title=\"Link to this heading\">\uf0c1</a></h2><p><strong>\u8be5\u793a\u4f8b\u4e2d\u7528\u5230\u4e86play_linkcraft</strong>\uff0c\u5217\u51fa\u673a\u5668\u4eba\u4e0a\u7684\u7075\u521b\u52a8\u4f5c\uff0c\u5e76\u4e14\u9009\u62e9\u4e00\u6761\u8fdb\u884c\u64ad\u653e</p>", "a[href=\"#id2\"]": "<h2 class=\"tippy-header\" style=\"margin-top: 0;\">\u63a5\u53e3\u8bf4\u660e<a class=\"headerlink\" href=\"#id2\" title=\"Link to this heading\">\uf0c1</a></h2>"}
skip_classes = ["headerlink", "sd-stretched-link"]

window.onload = function () {
    for (const [select, tip_html] of Object.entries(selector_to_html)) {
        const links = document.querySelectorAll(` ${select}`);
        for (const link of links) {
            if (skip_classes.some(c => link.classList.contains(c))) {
                continue;
            }

            tippy(link, {
                content: tip_html,
                allowHTML: true,
                arrow: true,
                placement: 'auto-start', maxWidth: 500, interactive: false, theme: 'material', duration: [300, 200], delay: [200, 100],

            });
        };
    };
    console.log("tippy tips loaded!");
};

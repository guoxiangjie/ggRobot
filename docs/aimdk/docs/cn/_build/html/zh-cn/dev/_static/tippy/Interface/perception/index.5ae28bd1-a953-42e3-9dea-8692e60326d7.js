selector_to_html = {"a[href=\"SLAM.html\"]": "<h1 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">5.5.2 </span>SLAM\uff08\u9009\u88c5\uff09<a class=\"headerlink\" href=\"#slam\" title=\"Link to this heading\">\uf0c1</a></h1><p><strong>SLAM\uff08\u540c\u6b65\u5b9a\u4f4d\u4e0e\u5efa\u56fe\uff09\u6a21\u5757\u63d0\u4f9b\u5730\u56fe\u6784\u5efa\u3001\u5730\u56fe\u83b7\u53d6\u548c\u91cd\u5b9a\u4f4d\u63a5\u53e3\uff0c\u652f\u6301\u673a\u5668\u4eba\u5728\u672a\u77e5\u73af\u5883\u4e2d\u5efa\u7acb\u5730\u56fe\u5e76\u57fa\u4e8e\u5df2\u6709\u5730\u56fe\u8fdb\u884c\u7cbe\u786e\u5b9a\u4f4d\u3002</strong></p>", "a[href=\"#id1\"]": "<h1 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">5.5 </span>\u611f\u77e5\u6a21\u5757\uff08\u9009\u88c5\uff09<a class=\"headerlink\" href=\"#id1\" title=\"Link to this heading\">\uf0c1</a></h1><p><strong>\u667a\u5143\u673a\u5668\u4ebaX2 SDK\u611f\u77e5\u6a21\u5757 - \u63d0\u4f9b\u591a\u6a21\u6001\u611f\u77e5\u80fd\u529b</strong></p>", "a[href=\"vision.html\"]": "<h1 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">5.5.1 </span>\u89c6\u89c9(\u5f85\u53d1\u5e03)<a class=\"headerlink\" href=\"#id1\" title=\"Link to this heading\">\uf0c1</a></h1>"}
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

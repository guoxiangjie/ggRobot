selector_to_html = {"a[href=\"#img-x2-sdk-interface\"]": "<figure class=\"align-left\" id=\"img-x2-sdk-interface\">\n<a class=\"reference internal image-reference\" href=\"../_images/SDK_interface.png\"><img alt=\"AgiBot X2 Ultra Secondary Development Interface Layout Diagram\" src=\"../_images/SDK_interface.png\" style=\"width: 100%;\"/>\n</a>\n<figcaption>\n<p><span class=\"caption-text\">AgiBot X2 Ultra Secondary Development Interface Layout Diagram</span><a class=\"headerlink\" href=\"#img-x2-sdk-interface\" title=\"Link to this image\">\uf0c1</a></p>\n</figcaption>\n</figure>", "a[href=\"#id1\"]": "<h1 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">1.5 </span>Secondary Development Interfaces (Ultra Edition)<a class=\"headerlink\" href=\"#id1\" title=\"Link to this heading\">\uf0c1</a></h1>"}
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

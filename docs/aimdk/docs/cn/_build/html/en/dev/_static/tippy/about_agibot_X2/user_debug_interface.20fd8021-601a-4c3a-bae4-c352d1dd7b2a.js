selector_to_html = {"a[href=\"#id2\"]": "<figure class=\"align-center\" id=\"id2\">\n<a class=\"reference internal image-reference\" href=\"../_images/user_debug_interface.png\"><img alt=\"AgiBot X2 Ultra User Debug Interface Layout (Numbers 1\u20135 correspond to the table above)\" src=\"../_images/user_debug_interface.png\" style=\"width: 60%;\"/>\n</a>\n<figcaption>\n<p><span class=\"caption-text\">AgiBot X2 Ultra User Debug Interface Layout (Numbers 1\u20135 correspond to the table above)</span><a class=\"headerlink\" href=\"#id2\" title=\"Link to this image\">\uf0c1</a></p>\n</figcaption>\n</figure>", "a[href=\"#id1\"]": "<h1 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">1.4 </span>User Debug Interfaces (Ultra Edition)<a class=\"headerlink\" href=\"#id1\" title=\"Link to this heading\">\uf0c1</a></h1>"}
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

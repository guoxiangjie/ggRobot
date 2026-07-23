selector_to_html = {"a[href=\"#id2\"]": "<h2 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">2.3.1 </span>Operation Steps<a class=\"headerlink\" href=\"#id2\" title=\"Link to this heading\">\uf0c1</a></h2><p><strong>1. Open the \u201cAdd Robot\u201d page</strong></p>", "a[href=\"#id1\"]": "<h1 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">2.3 </span>Remote Controller Connection<a class=\"headerlink\" href=\"#id1\" title=\"Link to this heading\">\uf0c1</a></h1><h2><span class=\"section-number\">2.3.1 </span>Operation Steps<a class=\"headerlink\" href=\"#id2\" title=\"Link to this heading\">\uf0c1</a></h2><p><strong>1. Open the \u201cAdd Robot\u201d page</strong></p>", "a[href=\"#id4\"]": "<figure class=\"align-center\" id=\"id4\">\n<a class=\"reference internal image-reference\" href=\"../_images/step_2_r.png\"><img alt=\"Tap Bluetooth settings\" src=\"../_images/step_2_r.png\" style=\"width: 60%;\"/>\n</a>\n<figcaption>\n<p><span class=\"caption-text\">Tap Bluetooth settings</span><a class=\"headerlink\" href=\"#id4\" title=\"Link to this image\">\uf0c1</a></p>\n</figcaption>\n</figure>", "a[href=\"#id3\"]": "<figure class=\"align-center\" id=\"id3\">\n<a class=\"reference internal image-reference\" href=\"../_images/step_1_r.png\"><img alt=\"Enter the Bluetooth connection interface\" src=\"../_images/step_1_r.png\" style=\"width: 60%;\"/>\n</a>\n<figcaption>\n<p><span class=\"caption-text\">Enter the Bluetooth connection interface</span><a class=\"headerlink\" href=\"#id3\" title=\"Link to this image\">\uf0c1</a></p>\n</figcaption>\n</figure>", "a[href=\"#id5\"]": "<figure class=\"align-center\" id=\"id5\">\n<a class=\"reference internal image-reference\" href=\"../_images/step_3_r.png\"><img alt=\"Select the controller and tap to connect\" src=\"../_images/step_3_r.png\" style=\"width: 60%;\"/>\n</a>\n<figcaption>\n<p><span class=\"caption-text\">Select the controller and tap to connect</span><a class=\"headerlink\" href=\"#id5\" title=\"Link to this image\">\uf0c1</a></p>\n</figcaption>\n</figure>"}
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

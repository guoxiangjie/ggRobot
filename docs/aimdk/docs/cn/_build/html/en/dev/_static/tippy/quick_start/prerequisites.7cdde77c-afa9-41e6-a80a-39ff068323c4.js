selector_to_html = {"a[href=\"#id2\"]": "<h1 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">4.2 </span>Complete the basic system configuration<a class=\"headerlink\" href=\"#id2\" title=\"Link to this heading\">\uf0c1</a></h1><p>And SDK example dependencies:</p>", "a[href=\"../about_agibot_X2/SDK_interface.html#img-x2-sdk-interface\"]": "<figure class=\"align-left\" id=\"img-x2-sdk-interface\">\n<a class=\"reference internal image-reference\" href=\"../_images/SDK_interface.png\"><img alt=\"AgiBot X2 Ultra Secondary Development Interface Layout Diagram\" src=\"../_images/SDK_interface.png\" style=\"width: 100%;\"/>\n</a>\n<figcaption>\n<p><span class=\"caption-text\">AgiBot X2 Ultra Secondary Development Interface Layout Diagram</span><a class=\"headerlink\" href=\"#img-x2-sdk-interface\" title=\"Link to this image\">\uf0c1</a></p>\n</figcaption>\n</figure>", "a[href=\"#id1\"]": "<h1 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">4.1 </span>Read the user guide to familiarize yourself with relevant terminology and safety precautions.<a class=\"headerlink\" href=\"#id1\" title=\"Link to this heading\">\uf0c1</a></h1>", "a[href=\"#aimdk-build\"]": "<h1 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">4.4 </span>Environment installation and configuration<a class=\"headerlink\" href=\"#aimdk-build\" title=\"Link to this heading\">\uf0c1</a></h1><p>Place the SDK into the target environment and extract it.</p>", "a[href=\"#id3\"]": "<h1 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">4.3 </span>Network connection<a class=\"headerlink\" href=\"#id3\" title=\"Link to this heading\">\uf0c1</a></h1><p>The AgiBot X2 Ultra supports multiple network access methods to connect to the onboard system:</p><p><strong>(1) Direct wired connection via the rear Ethernet port</strong> \u2014 Connect a network cable between the robot\u2019s <a class=\"reference internal\" href=\"../about_agibot_X2/SDK_interface.html#img-x2-sdk-interface\"><span class=\"std std-ref\">SDK development Ethernet port</span></a> and the host PC.</p>"}
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

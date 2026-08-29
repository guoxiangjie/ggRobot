selector_to_html = {"a[href=\"../../example/Cpp.html#cpp-play-linkcraft-action\"]": "<h2 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">6.2.27 </span>Play Linkcraft Action<a class=\"headerlink\" href=\"#cpp-play-linkcraft-action\" title=\"Link to this heading\">\uf0c1</a></h2><p>In this example, <strong>play_linkcraft</strong> is used to list the LinkCraft actions available on the robot and select one for playback.</p>", "a[href=\"#id2\"]": "<h2 class=\"tippy-header\" style=\"margin-top: 0;\">Interface Description<a class=\"headerlink\" href=\"#id2\" title=\"Link to this heading\">\uf0c1</a></h2>", "a[href=\"#id1\"]": "<h1 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">5.1.5 </span>LinkCraft Actions<a class=\"headerlink\" href=\"#id1\" title=\"Link to this heading\">\uf0c1</a></h1><p><strong>The LinkCraft action interface retrieves the list of LinkCraft action resources deployed on the robot and triggers playback of a specified action.</strong></p>", "a[href=\"#id3\"]": "<h2 class=\"tippy-header\" style=\"margin-top: 0;\">Programming Examples<a class=\"headerlink\" href=\"#id3\" title=\"Link to this heading\">\uf0c1</a></h2><p>For detailed programming examples and code descriptions, see:</p>", "a[href=\"../../example/Python.html#py-play-linkcraft-action\"]": "<h2 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">6.1.29 </span>Play Linkcraft Action<a class=\"headerlink\" href=\"#py-play-linkcraft-action\" title=\"Link to this heading\">\uf0c1</a></h2><p>In this example, <strong>play_linkcraft</strong> is used to list the LinkCraft actions available on the robot and select one for playback.</p>"}
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

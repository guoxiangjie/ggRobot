selector_to_html = {"a[href=\"#id2\"]": "<h2 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">5.6.1 </span>Check system status<a class=\"headerlink\" href=\"#id2\" title=\"Link to this heading\">\uf0c1</a></h2>", "a[href=\"../../example/Python.html#py-migrate-system-state\"]": "<h2 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">6.1.1 </span>Developer Mode<a class=\"headerlink\" href=\"#py-migrate-system-state\" title=\"Link to this heading\">\uf0c1</a></h2><p>Invoke the <code class=\"docutils literal notranslate\"><span class=\"pre\">'GetSystemState'</span></code> service to obtain the robot\u2019s current system status, and use <code class=\"docutils literal notranslate\"><span class=\"pre\">'MigrateSystemState'</span></code> to access the corresponding developer mode.</p><p><a class=\"reference internal\" href=\"../../Interface/system_state/index.html#tbl-system-state\"><span class=\"std std-ref\">Definition of Developer Mode</span></a></p>", "a[href=\"#id1\"]": "<h1 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">5.6 </span>Developer Mode<a class=\"headerlink\" href=\"#id1\" title=\"Link to this heading\">\uf0c1</a></h1><p><strong>AimDK Developer Mode for AgiBot X2 - By disabling the capabilities of Zhiyuan\u2019s native system software, it grants users greater system control privileges.</strong></p><p>Developers can enable a specific developer mode to deactivate the native AgiBot software, facilitating the deployment of their own applications and the takeover of certain system capabilities. This module complies with ROS2 standards, supports both C++ and Python programming languages, and provides developers with a unified switching interface.<strong>The mode-switch and locomotion interfaces provide core capabilities for switching motion modes and controlling walking/running.</strong></p>", "a[href=\"#id4\"]": "<h2 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">5.6.3 </span>Programming example<a class=\"headerlink\" href=\"#id4\" title=\"Link to this heading\">\uf0c1</a></h2><p>For detailed programming examples and code explanations, please refer to:</p>", "a[href=\"#id3\"]": "<h2 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">5.6.2 </span>Migrate to Develop mode<a class=\"headerlink\" href=\"#id3\" title=\"Link to this heading\">\uf0c1</a></h2>", "a[href=\"#id5\"]": "<h2 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">5.6.4 </span>Safety precautions<a class=\"headerlink\" href=\"#id5\" title=\"Link to this heading\">\uf0c1</a></h2>", "a[href=\"../../example/Cpp.html#cpp-migrate-system-state\"]": "<h2 class=\"tippy-header\" style=\"margin-top: 0;\"><span class=\"section-number\">6.2.1 </span>Developer Mode<a class=\"headerlink\" href=\"#cpp-migrate-system-state\" title=\"Link to this heading\">\uf0c1</a></h2><p>Invoke the <code class=\"docutils literal notranslate\"><span class=\"pre\">'GetSystemState'</span></code> service to obtain the robot\u2019s current system status, and use <code class=\"docutils literal notranslate\"><span class=\"pre\">'MigrateSystemState'</span></code> to access the corresponding developer mode.</p><p><a class=\"reference internal\" href=\"../../Interface/system_state/index.html#tbl-system-state\"><span class=\"std std-ref\">Definition of Developer Mode</span></a></p>"}
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

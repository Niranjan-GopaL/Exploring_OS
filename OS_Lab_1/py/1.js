console.log("oO08 iIlL1 g9qCGQ ~-+=>");
// â é ù ï ø ç Ã Ē Æ œ

specs = [1,2,4];

function updateGutters(cm) {
    var gutters = cm.display.gutters,
        __specs = cm.options.gutters;

    removeChildren(gutters);

    for (var i = 0; i < specs.length; ++i) {
        var gutterClass = __specs[i];
        var gElt = gutters.appendChild(
            elt(
                "div",
                null,
                "CodeMirror-gutter " + gutterClass
            )
        );
        if (gutterClass == "CodeMirror-linenumbers") {
            cm.display.lineGutter = gElt;
            gElt.style.width = (cm.display.lineNumWidth || 1) + "px";
        }
    }
    gutters.style.display = i ? "" : "none";
    updateGutterSpace(cm);

    return false;
}


import "../main.qbs" as DocProduct

DocProduct {
    name: "guiextension-api"
    type: "docs"

    docName: "guiextension-dev"
    Group {
        fileTagsFilter: ["docs"]
        qbs.install: true
        qbs.installDir: product.docPath
    }
}

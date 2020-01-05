module.exports = {
    entry: {
        index: "./src/index.js",
    },
    devServer: {
        port: 9000
    },
    output: {
        path: __dirname + "/dist/",
        filename: "[name].js",
    },
    node: {
        fd: "empty",
    },
};

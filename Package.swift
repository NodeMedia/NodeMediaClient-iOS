// swift-tools-version: 5.9
import PackageDescription

let package = Package(
    name: "NodeMediaClient",
    platforms: [
        .iOS(.v13)
    ],
    products: [
        .library(
            name: "NodeMediaClient",
            targets: ["NodeMediaClientTarget"]
        ),
    ],
    dependencies: [],
    targets: [
        // 1. Wrapper Target
        .target(
            name: "NodeMediaClientTarget",
            dependencies: [
                .target(name: "NodeMediaClient")
            ],
            path: "Sources/NodeMediaClientTarget",
            linkerSettings: [
                .linkedLibrary("z"),
                .linkedFramework("CoreMedia"),
                .linkedFramework("AudioToolbox"),
                .linkedFramework("VideoToolbox"),
                .linkedFramework("AVFoundation")
            ]
        ),
        // 2. 二进制 Target：通过远程链接与 SHA256 校验和引入
        .binaryTarget(
            name: "NodeMediaClient",
            url: "https://cdn.nodemedia.cn/NodeMediaClient/NodeMediaClient.xcframework-4.1.7.zip",
            checksum: "4273447d978951eda82f674d87904ec9034bbcfea223167fa44af033750100f6"
        )
    ]
)
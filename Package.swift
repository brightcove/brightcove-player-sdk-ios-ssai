// swift-tools-version:5.5
// The swift-tools-version declares the minimum version of Swift required to build this package.
// https://developer.apple.com/documentation/xcode/creating_a_standalone_swift_package_with_xcode?language=objc

import PackageDescription

let BrightcovePlayerSDK = Package(
    name: "SSAI Plugin for Brightcove Player SDK",
    platforms: [
        .iOS(.v12), .tvOS(.v12)
    ],
    products: [
        .library(
            name: "BrightcoveSSAI",
            targets: ["BrightcoveSSAI"]),
        .library(
            name: "BrightcoveSSAI & Open Measurement",
            targets: ["BrightcoveSSAI", "OMSDK_Brightcove"])
    ],
    targets: [
        .binaryTarget(
            name: "BrightcoveSSAI",
            path: "xcframework/BrightcoveSSAI.xcframework"
        ),
        .binaryTarget(
            name: "OMSDK_Brightcove",
            path: "xcframework/OMSDK_Brightcove.xcframework"
        )
    ]
)

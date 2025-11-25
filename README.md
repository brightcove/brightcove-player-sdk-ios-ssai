# SSAI Plugin for Brightcove Player SDK for iOS, version 7.2.0.8

Supports Mac Catalyst 13.0 and above since SDK release v6.10.3.

## Installation

The SSAI plugin for Brightcove Player SDK for iOS provides a dynamic library framework for installation.

### CocoaPods

You can use [CocoaPods][cocoapods] to add the SSAI Plugin for Brightcove Player SDK to your project.  You can find the latest `Brightcove-Player-SSAI` podspec [here][podspecs].

#### CocoaPod Podfile example:

```bash
source 'https://github.com/brightcove/BrightcoveSpecs.git'

use_frameworks!
platform :ios, '12.0'

target 'MyVideoPlayer' do
  pod 'Brightcove-Player-SSAI'
end
```

#### XCFramework example:

XCFramework will be installed appending the `/XCFramework` subspec in the pod.

```bash
source 'https://github.com/brightcove/BrightcoveSpecs.git'

use_frameworks!
platform :ios, '12.0'

target 'MyVideoPlayer' do
  pod 'Brightcove-Player-SSAI/XCFramework'
end
```

When updating your installation, it's a good idea to refresh the local copy of your BrightcoveSpecs repository so that you have the latest podspecs locally, just like you would update your CococaPods master repository.

Typically if you use `pod update` in Terminal this will happen automatically, or alternatively you can update explicitly with `pod repo update brightcove`. (Your BrightcoveSpecs repository may have a different name if you explicitly added it to your list of podspecs repos.)

### Manual

To add the SSAI Plugin for Brightcove Player SDK to your project manually:

1. Install the latest version of the [Brightcove Player SDK][bcovsdkreleases].
1. Download the latest zip'ed release of the BrightcoveSSAI plugin from our [release page][release].
1. Add `BrightcoveSSAI.framework` or `BrightcoveSSAI.xcframework` to your project.
1. Add `OMSDK_Brightcove.xcframework` to your project.
1. On the "Build Settings" tab of your application target, ensure that the "Framework Search Paths" include the paths to the frameworks. This should have been done automatically unless the framework is stored under a different root directory than your project.
1. On the "General" tab of your application target, add 'BrightcoveSSAI.framework' or 'BrightcoveSSAI.xcframework' to the "Frameworks, Libraries, Embedded Content" section. 
1. (**Open Measurement** support) If you need to support OM in your app add 'OMSDK_Brightcove.xcframework' to the "Frameworks, Libraries, Embedded Content" section.
1. (**Mac Catalyst and Open Measurement** only) In the "Filter" for `OMSDK_Brightcove.xcframework`, ensure that only the value `iOS` is selected.
1. (**Universal Framework** only) On the "Build Phases" tab, add a "Run Script" phase with the command `bash ${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/BrightcoveSSAI.framework/strip-frameworks.sh`. Check "Run script only when installing". This will remove unneeded architectures from the build, which is important for App Store submission.
1. (**Apple Silicon with Universal Framework** only) On the "Build Settings" tab of your application target:
    * Ensure that `arm64` has been added to your "Excluded Architectures" build setting for `Any iOS Simulator SDK`.

### Swift Package Manager

To add the SSAI Plugin for Brightcove Player SDK to your project with Swift Package Manager: 

1. First [follow the steps][corespm] to add the Core XCFramework with Swift Package Mananger.
1. Add the SSAI package to Swift Package Manager using `https://github.com/brightcove/brightcove-player-sdk-ios-ssai.git`.
1. You can then select either `BrightcoveSSAI` or `BrightcoveSSAI & Open Measurement` if you need OM support.

[corespm]: https://github.com/brightcove/brightcove-player-sdk-ios#swift-package-manager

### Imports

The SSAI Plugin for Brightcove Player SDK for iOS can be imported using:
```swift
import BrightcoveSSAI
```

[cocoapods]: http://cocoapods.org
[podspecs]: https://github.com/brightcove/BrightcoveSpecs/tree/master/Brightcove-Player-SSAI
[release]: https://github.com/brightcove/brightcove-player-sdk-ios-ssai/releases
[bcovsdkreleases]: https://github.com/brightcove/brightcove-player-sdk-ios/releases

## Quick Start

BrightcoveSSAI is a plugin for [Brightcove Player SDK for iOS][bcovsdk] that provides support for Brightcove Server Side Ad Insertion.

```swift
[1] let displayContainer = BCOVSSAIAdComponentDisplayContainer(companionSlots: [])

    let sdkManager = BCOVPlayerSDKManager.sharedManager()

[2] let playbackController = sdkManager.createSSAIPlaybackController()

[3] playbackController.add(displayContainer)

[4] videoView.addSubview(playerView)

    let policyKey = "<your-policy-key>"
    let accountID = "<your-account-id>"
    let videoID = "<your-video-id>"
    let playbackService = BCOVPlaybackService(withAccountId: accountID,
                                              policyKey: policyKey)
    let configuration = [
        BCOVPlaybackService.ConfigurationKeyAssetID: videoID
    ]
    let queryParameters = [
        BCOVPlaybackService.ParamaterKeyAdConfigId: "<valid-ad-config-id>"
    ]
[5] playbackService.findVideo(withConfiguration: configuration,
                              queryParameters: queryParameters) { (video: BCOVVideo?,
                                                                   jsonResponse: Any?,
                                                                   error: Error?) in
        if let video {
[6]        playbackController.setVideos([video])
        playbackController.play()
        }
    }
```

To summarize:

1. First create a `BCOVSSAIAdComponentDisplayContainer`. This object will help manage companion slots. Pass in the companion slots that you have, if any.
1. BrightcoveSSAI adds some category methods to `BCOVPlaybackManager`. The first of these is `-createSSAIPlaybackControllerWithViewStrategy:`. Use this method to create your playback controller. You will typically pass `nil` for the view strategy.
1. In order for the `BCOVSSAIAdComponentDisplayContainer` to display ad information and populate companion ad views, it must be added as a session consumer.
1. Add the playback controller's view to the video container in your own view hierarchy.
1. Request the video or playlist from the Playback Service. When using a Unicorn Once-style VMAP URL, create the BCOVVideo object directly using `[BCOVVideo videoWithURL:<unicorn-style-url>]`.
1. Load the video into the playback controller.

## Open Measurement

Open Measurement (OM) is an IAB Tech Lab initiative aimed to standardize viewability and verification measurement. Using OM, publishers can access multiple SDKs collapsed into a single integration, simplifying maintenance without sacrificing functionality.
The SDK provided by IAB Tech Lab can be used in the SSAI Plugin for Brightcove Player for iOS. Since v6.10.3 the OMSDK is not installed along with the SSAI plugin. You can install it in your iOS apps adding the pod in your Podfile:

Universal Framework (Fat Framework) example:

```bash
  pod 'Brightcove-Player-SSAI'
  pod 'Brightcove-Player-OpenMeasurement'
```

XCFramework example:

```bash
  pod 'Brightcove-Player-SSAI/XCFramework'
  pod 'Brightcove-Player-OpenMeasurement'
```

To take the advantage of using IAB Open Measurement, the SSAI Plugin for iOS provides a new signature:

```swift
sdkManager.createSSAISessionProvider(withUpstreamSessionProvider:omidPartner:)
```

The `omidPartner` string identifies the integration. The value can not be empty or nil, if partner is not available, use "unknown". The IAB Tech Lab will assign a unique partner name to you at the time of integration, so this is the value you should use here. However, if the OpenMeasurement SDK is not embedded in your iOS app the `omidPartner` string will be ignored and OM will not take effect. The `sdkManager.createSSAISessionProvider(withUpstreamSessionProvider:omidPartner:)` signature is not available for Mac Catalyst.

### Open Measurement and Mac Catalyst

Open Measurement can not be used in Mac Catalyst apps due IAB Tech Lab does not provide the necessary slice. If you need to create an app that shares code between iOS and Mac Catalyst, and uses Open Measurement for iOS app follow the steps:

1. Remove 'Brightcove-Player-OpenMeasurement' from your Podfile.
1. Update your pods running `pod update`.
1. Download the latest zip'ed release of the `BrightcoveSSAI` plugin from our [release page][release].
1. Add `OMSDK_Brightcove.xcframework` to your project.
1. On the "General" tab of your application target, add `OMSDK_Brightcove.xcframework` to the "Frameworks, Libraries, Embedded Content" section.
1. In the "Filter" for `OMSDK_Brightcove.xcframework`, ensure that only the value `iOS` is selected.

## Using a custom VMAP source URL

If you have a custom VMAP source URL and do not need to use the `BCOVPlaybackService` you can manually create a `BCOVVideo` with your URL like this:

```swift
if let url = URL(string: "https://sdks.support.brightcove.com/assets/ads/ssai/sample-vmap.xml") {
    let video = BCOVVideo.video(withURL: url)
    playbackController.setVideos([video])
}
```

## Using VMAP XML data

If you have VMAP XML data you can manually create a `BCOVVideo` with your data like this:

```swift
// If using FairPlay DRM you'll need to construct the key_systems dictionary
// otherwise you can pass `nil` for the properties value.
let properties = [
    "key_systems": [
        "com.apple.fps.1_0": [
            "key_request_url": "<insert key request URL>",
            "certificate_url": "<insert certificate URL>"
        ]
    ]
]

let source = BCOVSource(vmapxmlData: vmapData, properties: properties)
let video = BCOVVideo(withSource: source, cuePoints: nil, properties: nil)
playbackController.setVideos([video])
```

## Obtaining Ad Playback Information

BrightcoveSSAI provides ad playback information via the `BCOVPlaybackControllerAdsDelegate`. For example, if you want to hide your controls during an ad, you could implement `-[BCOVPlaybackControllerAdsDelegate playbackController:playbackSession:didEnterAdSequence:]` to hide them.

For more information on how to use these delegate methods, please see [Brightcove Player SDK for iOS][bcovsdk].

[bcovsdk]: https://github.com/brightcove/brightcove-player-sdk-ios

## Seeking

The BrightcoveSSAI plugin provides a seeking function that should be used when implementing controls. This seek function is exposed on the session through the `providerExtension` property. Here is how it is used:

```swift
let contentTimeToSeekTo: CMTime = <calulation-from-scrub-bar>
currentSession?.providerExtension.ssai_seek(to: contentTimeToSeekTo, completionHandler: { [weak self] finished in
    if finished {
        self?.playbackController.play()
    }
})
```
    
The `completionHandler` will execute at the completion of a successful seek. It will not execute if a seek was already initiated by a previous call to `-[BCOVSessionProviderExtension ssai_seekToTime:completionHandler:]` or if an ad is playing back. To test whether a seek attempt can be made, check the `-[BCOVSessionProviderExtension ssai_canSeek]` property. For more information on both of these methods, be sure to read the [headerdoc][ssai_extensions].

[ssai_extensions]: https://github.com/brightcove/brightcove-player-sdk-ios-ssai/blob/master/ios/BrightcoveSSAI.framework/Headers/BCOVSSAIComponent.h

## Seek Without Ads

The BrightcovePlayerSDK provides the `adsDisabled` BOOL property for disabling ads while seeking, allowing an application to resume playback without requiring the end-user to view previously played ads.

In preparation for seeking, disable `autoPlay` when setting up the `BCOVPlaybackController`.

Ad-disabling logic should be added to the `kBCOVPlaybackSessionLifecycleEventReady` handler of the `-playbackController:playbackSession:didReceiveLifecycleEvent:` method of your `BCOVPlaybackController` delegate.

```swift
func playbackController(_ controller: BCOVPlaybackController,
                        playbackSession session: BCOVPlaybackSession,
                        didReceive lifecycleEvent: BCOVPlaybackSessionLifecycleEvent) {
    if lifecycleEvent.eventType == kBCOVPlaybackSessionLifecycleEventReady {
        // disable ads.
        playbackController.adsDisabled = true

        // seek somewhere into the video content.
        session.providerExtension.ssai_seek(to: resumeTime) { [weak self] finished in
            // re-enable ads.
            self?.playbackController.adsDisabled = false

            // open the shutter
            self?.playbackController.shutterFadeTime = 0.25
            self?.playbackController.shutter = false
        }
    }
}
```

When calling `ssai_seekToTime:completionHandler:` to resume playback at a particular time, the first frame of the video might be visible until the seek completes. For a cleaner presentation, temporarily cover the video view during seeking by setting the `shutter` property of BCOVPlabackController to `YES` before calling `-setVideos:`. When seeking is complete, dismiss the shutter by setting the `shutter` property to `NO`. The `shutterFadeTime` property defines the duration of the shutter fade animation.

```swift
playbackController = sdkManager.createSSAIPlaybackController()

// activate the shutter before loading video.
playbackController.shutterFadeTime = 0.0
playbackController.shutter= true

// load the video
```

Note that for performance reasons, small tolerances are built into video seeking. A seek to a content playhead position which is close to the start of an ad sequence can result in a seek to the start of the ad sequence. If autoPlay is NO in this case, AVPlayer will be paused on the first frame of the ad sequence.

## Access to VMAP Response Data

Should you want access to the VMAP response data you can subscribe to the `kBCOVSSAIVMAPResponseReceivedNotification` notification. Once received, the notification's userInfo dictionary will contain the VMAP response as NSData. You can use the `kBCOVSSAIVMAPResponseReceivedNotificationDataUserInfoKey` constant to access it from userInfo. Since you may have multiple playback controllers, and thus multiple VMAP responses, you can check the notification's object, `id playbackController = notification.object` to verify which video the VMAP data is for. Additionally, when you subscribe to the notification you can set a playback controller as the object so that only VMAP data notifications regarding that playback controller will be received. For example:

```swift
NotificationCenter.default.addObserver(self,
                                       selector: #selector(vmapResponseReceived(_:)),
                                       name: NSNotification.Name.bcovssaivmapResponseReceived,
                                       object: nil)
```

You can also access the VMAP response data through the `BCOVOUXSession` object:

```swift
func playbackController(_ controller: BCOVPlaybackController,
                        didAdvanceTo session: BCOVPlaybackSession) {
    if (session.responds(to: NSSelectorFromString("vmapResponseData")))
    {
        let vmapResponseData = (session as? NSObject)?.value(forKeyPath: "vmapResponseData") as? Data
        var xmlString: String? = nil
        if let vmapResponseData = vmapResponseData {
            xmlString = String(data: vmapResponseData, encoding: .utf8)
        }
        print("VMAP XML: \(xmlString ?? "")")
    }
}
```

## AVPlayerViewController Support

### Enforcing Linear Playback

If you'd like to enforce linear playback durings ads while using AVPlayerViewController all you have to do is set AVPlayerViewController's delegate to one of your classes and add the following:

```swift
// MARK: AVPlayerViewControllerDelegate

func playerViewController(_ playerViewController: AVPlayerViewController,
                          willPresent interstitial: AVInterstitialTimeRange) {
    playerViewController.requiresLinearPlayback = true
}

func playerViewController(_ playerViewController: AVPlayerViewController,
                          didPresent interstitial: AVInterstitialTimeRange) {
    playerViewController.requiresLinearPlayback = false
}
```

### Displaying an Ad UI

You can also add your own advertising UI using these methods as well by adding views to AVPlayerViewController's `contentOverlayView` when `willPresentInterstitialTimeRange:` is called and and removing or hiding it when `didPresentInterstitialTimeRange:` is called. Here is an example:

```swift
func displayAdUI(withAdDuration duration: TimeInterval) {
    // UI Setup
    // Adding a subview to the AVPlayerViewController's contentOverlayView
}

func hideAdUI() {
    // Hide the view/s that were added in displayAdUI:
}

// MARK: AVPlayerViewControllerDelegate
func playerViewController(_ playerViewController: AVPlayerViewController,
                          willPresent interstitial: AVInterstitialTimeRange) {
    displayAdUI(withAdDuration: CMTimeGetSeconds(interstitial.timeRange.duration))
}

func playerViewController(_ playerViewController: AVPlayerViewController,
                          didPresent interstitial: AVInterstitialTimeRange) {
    hideAdUI()
}
```

You may also wish to prevent users from seeking over an ad. Here is an example of how to prevent that:

```swift
// MARK: AVPlayerViewControllerDelegate

func playerViewController(_ playerViewController: AVPlayerViewController,
                          timeToSeekAfterUserNavigatedFrom oldTime: CMTime,
                          to targetTime: CMTime) -> CMTime {
    // Check to see if we'll be seeking over any interstitials
    // If we are, seek to the beginning of the last interstitial
    // and save the targetTime so we can seek after the interstitial
    // has finished.

    guard let interstitialTimeRanges = playerViewController.player?.currentItem?.interstitialTimeRanges else {
        return targetTime
    }

    var timeRanges = [AVInterstitialTimeRange]()
    for interstitialTimeRange in interstitialTimeRanges {
        let startTime = interstitialTimeRange.timeRange.start
        if CMTimeCompare(targetTime, startTime) == 1 && CMTimeCompare(startTime, oldTime) == 1 {
            timeRanges.append(interstitialTimeRange)
        }
    }

    // If we encounter an ad we should seek to the start time
    // of the ad and save the desired seek time to we can seek
    // to it after the ad completes
    if timeRanges.count > 0 {
        seekToTime = targetTime
        if let lastTimeRange = timeRanges.last {
            return lastTimeRange.timeRange.start
        }
    }

    return targetTime
}

// MARK: BCOVPlaybackControllerDelegate

func playbackController(_ controller: BCOVPlaybackController,
                        playbackSession ession: BCOVPlaybackSession,
                        didExitAdSequence adSequence: BCOVAdSequence) {
    // If we encountered an ad while seeking we can now
    // seek to the desired location
    if CMTimeCompare(seekToTime, .invalid) != 0 {
        playerViewController.player?.seek(to: seekToTime)
        seekToTime = .invalid
    }
}
```

If you'd like to prevent a pre-roll ad from playing again here in an example of how to approach that:

```swift
func playerViewController(_ playerViewController: AVPlayerViewController,
                          willPresent interstitial: AVInterstitialTimeRange) {
    if CMTimeCompare(interstitial.timeRange.start, .zero) == 0 && didPlayPreroll {
        playerViewController.player?.seek(to: interstitial.timeRange.duration)
    }
}

func playerViewController(_ playerViewController: AVPlayerViewController,
                          didPresent interstitial: AVInterstitialTimeRange) {
    if CMTimeCompare(interstitial.timeRange.start, .zero) == 0 {
        didPlayPreroll = true
    }
}
```

## Picture-in-Picture

The Brightcove SSAI plugin can be used with Brightcove's Picture-in-Picture support.

When entering and exiting an ad sequence the `requiresLinearPlayback` property on the current `AVPictureInPictureController` will be enabled and disabled accordingly so that users can not skip ad breaks.

### Using a Custom Playback Rate

If you want to use a [custom playback rate](https://github.com/brightcove/brightcove-player-sdk-ios#playback-rate) along with using [AVPlayerViewController](https://github.com/brightcove/brightcove-player-sdk-ios#using-an-avplayerviewcontroller-with-a-bcovplaybackcontroller) you'll need to disable the automatic generation of `interstitialTimeRanges`. You can do this by setting the `generateInterstitialTimeRanges` property on your `BCOVPlaybackController` to `NO`.

## SSAI URL Variables

SSAI supports [URL variables](https://apis.support.brightcove.com/ssai/getting-started/video-cloud-ssai-ad-config-api.html#URL_variables) which allow you to pass arbitrary data from the content.vmap URL into the SSAI system. For example the URL `content.vmap?foo={{url.foo}}&bar={{url.bar}}` would become `content.vmap?foo=123&bar=hello` after replacing each `{{url.<variableName>}}` variable with a real value.

Here is an example of how you could perform the variable replacement:

```swift
func requestContentFromPlaybackService() {
    ...
    playbackService.findVideo(withConfiguration: configuration,
                              queryParameters: queryParameters,
                              completion: { [weak self] (video: BCOVVideo?,
                                                         jsonResponse: Any?,
                                                         error: Error?) in
        guard let jsonResponse = jsonResponse as? [AnyHashable:Any] else {
            return
        }
        let updatedJSON = self?.replaceSSAIVariablesInJSON(jsonResponse)
        if let updatedVideo = BCOVPlaybackService.videoFromJSONDictionary(updatedJSON as Any) {
            self?.playbackController.setVideos([updatedVideo])
        }
    })
}

func replaceSSAIVariablesInJSON(_ jsonResponse: [AnyHashable: Any]) -> [AnyHashable: Any] {
    guard let sources = jsonResponse["sources"] as? [[AnyHashable: Any]] else {
        return jsonResponse
    }
    var updatedJson = jsonResponse
    var updatedSources = [[AnyHashable: Any]]()
    for source in sources {
        guard let vmapURL = source["vmap"] as? String else {
            continue
        }
        if vmapURL.contains("{{url.") {
            var updatedSource = source
            updatedSource["vmap"] = replaceSSAIVariablesInVMAPURL(vmapURL)
            updatedSources.append(updatedSource)
        } else {
            updatedSources.append(source)
        }
    }
    updatedJson["sources"] = updatedSources
    return updatedJson
}

func replaceSSAIVariablesInVMAPURL(_ vmapURL: String) -> String {
    let replacementValues = [
        "foo": "123",
        "bar": "hello"
    ]
    var updatedURL = vmapURL
    for key in replacementValues.keys {
        guard let replacementValue = replacementValues[key] else {
            continue
        }
        let valueToReplace = "{{url.\(key)}}"
        updatedURL = updatedURL.replacingOccurrences(of: valueToReplace, with: replacementValue)
    }
    return updatedURL
}
```

## Known Issues

* Because tvOS does not support Web browsing, Companion Ads, Learn More and all ad clickthroughs are ignored on that platform.

* You cannot use BrightcoveSSAI with any other Brightcove plugins except for the BrightcoveFairPlay plugin, or the BrightcoveIMA plugin (for pre-roll ads only).

* If you want to use the BrightcoveSSAI plugin along with the BrightcoveFairPlay plugin then the BrightcoveFairPlay plugin must be the `upstreamSessionProvider` of the SSAI session provider.

* The SSAI plugin does not support playing non-SSAI content. If you need to play non-SSAI content you need to create another playback controller that does not use the SSAI plugin.

## Support

If you have questions, need help or want to provide feedback, please use the [Support Portal](https://supportportal.brightcove.com/s/login/) or contact your Account Manager.  To receive notification of new SDK software releases, subscribe to the Brightcove Native Player SDKs [Google Group](https://groups.google.com/g/brightcove-native-player-sdks).

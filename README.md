# SSAI Plugin for Brightcove Player SDK for iOS, version 6.7.4.1018

Requirements
============

- Xcode 11.0+
- ARC

Supported Platforms
===================
iOS 11.0 and above.

tvOS 11.0 and above.

Installation
============
The SSAI plugin for Brightcove Player SDK for iOS provides two installation packages; a static library framework and a dynamic library framework.

CocoaPods
--------------

You can use [CocoaPods][cocoapods] to add the SSAI Plugin for Brightcove Player SDK to your project.  You can find the latest `Brightcove-Player-SSAI` podspec [here][podspecs].

Static framework example:

```
source 'https://github.com/brightcove/BrightcoveSpecs.git'

use_frameworks!
platform :ios, 11.0'

target 'MyVideoPlayer' do
  pod 'Brightcove-Player-SSAI'
end
```
    
Dynamic framework example:

```
source 'https://github.com/brightcove/BrightcoveSpecs.git'

use_frameworks!
platform :ios, '11.0'

target 'MyVideoPlayer' do
  pod 'Brightcove-Player-SSAI/dynamic'
end
```

When updating your installation, it's a good idea to refresh the local copy of your BrightcoveSpecs repository so that you have the latest podspecs locally, just like you would update your CococaPods master repository.

Typically if you use `pod update` in Terminal this will happen automatically, or alternatively you can update explicitly with `pod repo update brightcove`. (Your BrightcoveSpecs repository may have a different name if you explicitly added it to your list of podspecs repos.)

Manual
--------------

To add the SSAI Plugin for Brightcove Player SDK to your project manually:

1. Install the latest version of the [Brightcove Player SDK][bcovsdk].
2. Download the latest zip'ed release of the BrightcoveSSAI plugin from our [release page][release].
3. Add `BrightcoveSSAI.framework` to your project.
4. On the "Build Settings" tab of your application target, ensure that the "Framework Search Paths" include the path to the framework. This should have been done automatically unless the framework is stored under a different root directory than your project.
5. (Dynamic Framework only) On the "General" tab of your application target, add 'BrightcoveSSAI.framework' to the "Embedded Binaries" section.
6. (Dynamic Framework only) On the "Build Phases" tab, add a "Run Script" phase with the command `bash ${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/BrightcoveSSAI.framework/strip-frameworks.sh`. Check "Run script only when installing". This will remove unneeded architectures from the build, which is important for App Store submission.
7. (Static Framework only) On the "Build Settings" tab of your application target, add `-ObjC` to the "Other Linker Flags" build setting.

Imports
--------------
The SSAI Plugin for Brightcove Player SDK for iOS can be imported into code a few different ways; `@import BrightcoveSSAI;`, `#import <BrightcoveSSAI/BrightcoveSSAI.h>` or `#import <BrightcoveSSAI/[specific class].h>`.

[cocoapods]: http://cocoapods.org
[podspecs]: https://github.com/brightcove/BrightcoveSpecs/tree/master/Brightcove-Player-SSAI
[release]: https://github.com/brightcove/brightcove-player-sdk-ios-ssai/releases

Quick Start
===========
BrightcoveSSAI is a plugin for [Brightcove Player SDK for iOS][bcovsdk] that provides support for Brightcove Server Side Ad Insertion.

    [1] BCOVSSAIAdComponentDisplayContainer *displayContainer = [[BCOVSSAIAdComponentDisplayContainer alloc] initWithCompanionSlots:@[]];
        
        BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];

    [2] id<BCOVPlaybackController> playbackController = [sdkManager createSSAIPlaybackController];

    [3] [playbackController addSessionConsumer:displayContainer];
    
    [4] [self.videoContainer addSubview:playbackController.view];
    
    [5] BCOVPlaybackService *playbackService = [[BCOVPlaybackService alloc] initWithAccountId:accoundId
                                                                                    policyKey:policyKey];
        [playbackService findVideoWithVideoID:videoID
                                   parameters:@{ kBCOVPlaybackServiceParamaterKeyAdConfigId: <valid-ad-config-id> }
                                   completion:^(BCOVVideo *video,
                                                NSDictionary *jsonResponse,
                                                NSError *error) {
    
    [6]                              [playbackController setVideos:@[ video ]];
                                     [playbackController play];
    
                               }];

To summarize:

1. First create a `BCOVSSAIAdComponentDisplayContainer`. This object will help manage companion slots. Pass in the companion slots that you have, if any.
1. BrightcoveSSAI adds some category methods to `BCOVPlaybackManager`. The first of these is `-createSSAIPlaybackControllerWithViewStrategy:`. Use this method to create your playback controller. You will typically pass `nil` for the view strategy.
1. In order for the `BCOVSSAIAdComponentDisplayContainer` to display ad information and populate companion ad views, it must be added as a session consumer.
1. Add the playback controller's view to the video container in your own view hierarchy.
1. Request the video or playlist from the Playback Service. When using a Unicorn Once-style VMAP URL, create the BCOVVideo object directly using `[BCOVVideo videoWithURL:<unicorn-style-url>]`.
1. Load the video into the playback controller.

If you have questions or need help, visit the support forum for Brightcove Native Player SDKs at [https://groups.google.com/forum/#!forum/brightcove-native-player-sdks][forum] .

[forum]: https://groups.google.com/forum/#!forum/brightcove-native-player-sdks

Migrating OnceUX to SSAI
=======

The BrightcoveSSAI plugin framework is taking the place of BrightcoveOUX. BrightcoveSSAI supports all the current features of BrightcoveOUX, however future updates will only be added to BrightcoveSSAI. Follow these instructions to migrate your OnceUX application to Brightcove SSAI.

1) If you install Brightcove plugins using CocoaPods, update your Podfile by changing `Brightcove-Player-OnceUX` to `Brightcove-Player-SSAI`, for example this:
```
target 'MyVideoPlayer' do
	pod 'Brightcove-Player-OnceUX/dynamic'
end
```
becomes this:
```
target 'MyVideoPlayer' do
	pod 'Brightcove-Player-SSAI/dynamic'
end
```
If you use static frameworks, leave off `/dynamic` like this: `pod 'Brightcove-Player-SSAI'`, then run `'pod update'`.

If you install the Brightcove plugins manually, delete the Brightcove-Player-OnceUX framework from your Xcode project and follow the steps above to manually add the Brightcove-Player-SSAI framework. Alternatively, you can change the name of the BrightcoveOUX framework to BrightcoveSSAI using the Xcode File Inspector, and update the Framework Search Path in the Build Settings for your app target.

2) In your source code, for all @import / #import statements, data types, method names, properties, constants and protocols which refer to the BrightcoveOUX framework, change every occurrence of "OUX" to "SSAI". A partial list is here:
 
 * `@import BrightcoveOUX;` is now `@import BrightcoveSSAI;`
 * `createOUXSessionProviderWithUpstreamSessionProvider` is now `createSSAISessionProviderWithUpstreamSessionProvider`
 * `createOUXPlaybackControllerWithViewStrategy` is now `createSSAIPlaybackControllerWithViewStrategy`
 * `oux_seekToTime` is now `ssai_seekToTime`
 * `BCOVOUXAdComponentDisplayContainer` is now `BCOVSSAIAdComponentDisplayContainer`
 * `BCOVOUXCompanionSlot` is now `BCOVSSAICompanionSlot`

Obtaining Ad Playback Information
=======
BrightcoveSSAI provides ad playback information via the `BCOVPlaybackControllerAdsDelegate`. For example, if you want to hide your controls during an ad, you could implement `-[BCOVPlaybackControllerAdsDelegate playbackController:playbackSession:didEnterAdSequence:]` to hide them.

For more information on how to use these delegate methods, please see [Brightcove Player SDK for iOS][bcovsdk].

[bcovsdk]: https://github.com/brightcove/brightcove-player-sdk-ios

Seeking
=======

The BrightcoveSSAI plugin provides a seeking function that should be used when implementing controls. This seek function is exposed on the session through the `providerExtension` property. Here is how it is used:
    
    
    CMTime contentTimeToSeekTo = <calculation-from-scrub-bar>;
    [self.currentSession.providerExtension ssai_seekToTime:contentTimeToSeekTo completionHandler:^(BOOL finished) {
    
        if (finished)
        {
            [self.currentSession.player play];
        }
    
    }];
    
The `completionHandler` will execute at the completion of a successful seek. It will not execute if a seek was already initiated by a previous call to `-[BCOVSessionProviderExtension ssai_seekToTime:completionHandler:]` or if an ad is playing back. To test whether a seek attempt can be made, check the `-[BCOVSessionProviderExtension ssai_canSeek]` property. For more information on both of these methods, be sure to read the [headerdoc][ssai_extensions].

[ssai_extensions]: https://github.com/brightcove/brightcove-player-sdk-ios-ssai/blob/master/ios/static/BrightcoveSSAI.framework/Headers/BCOVSSAIComponent.h

Seek Without Ads
=======

The BrightcovePlayerSDK provides the `adsDisabled` BOOL property for disabling ads while seeking, allowing an application to resume playback without requiring the end-user to view previously played ads.

Ad-disabling logic should be added to the `kBCOVPlaybackSessionLifecycleEventReady` handler of the `-playbackController:playbackSession:didReceiveLifecycleEvent:` method of your `BCOVPlaybackController` delegate.

	- (void)playbackController:(id<BCOVPlaybackController>)controller
	           playbackSession:(id<BCOVPlaybackSession>)session
	  didReceiveLifecycleEvent:(BCOVPlaybackSessionLifecycleEvent *)lifecycleEvent
	  {
	    if ([kBCOVPlaybackSessionLifecycleEventReady isEqualToString:lifecycleEvent.eventType])
	    {
	      // disable ads.
	      _playbackController.adsDisabled = YES;
	
	      // seek somewhere into the video content.
	      [session.providerExtension ssai_seekToTime:resumeTime completionHandler:^(BOOL finished)
	      {
	        // re-enable ads.
	        _playbackController.adsDisabled = NO;
	
	        // open the shutter.
	        _playbackController.shutterFadeTime = 0.25;
	        _playbackController.shutter = NO;
	    }];
	  }

When calling `ssai_seekToTime:completionHandler:` to resume playback at a particular time, the first frame of the video might be visible until the seek completes. For a cleaner presentation, temporarily cover the video view during seeking by setting the `shutter` property of BCOVPlabackController to `YES` before calling `-setVideos:`. When seeking is complete, dismiss the shutter by setting the `shutter` property to `NO`. The `shutterFadeTime` property defines the duration of the shutter fade animation.

	self.playbackController = [sdkManager createSSAIPlaybackController];

	// activate the shutter before loading video.
	self.playbackController.shutterFadeTime = 0.0;
	self.playbackController.shutter = YES;
	
	// load the video.

Player UI Built-In Controls
===========================

The BrightcovePlayerSDK provides a built-in set of UI controls that can be used with the SSAI plugin for both basic playback and ad controls. To use the controls, create a `BCOVPUIPlayerView`, and associate it with your SSAI playback controller.

First, create a playerView property in your class.

     @property (nonatomic) BCOVPUIPlayerView *playerView;

Create the `BCOVPUIPlayerView` instance and save a reference to the object.

     BCOVPUIBasicControlView *controlView = [BCOVPUIBasicControlView basicControlViewWithVODLayout];
     self.playerView = [[BCOVPUIPlayerView alloc] initWithPlaybackController:nil options:nil controlsView:controlView];
     // Insert the playerView into your own video view.
     [self.videoContainer addSubview:self.playerView];

You'll need to set up the layout for the player view, you can do this with Auto Layout or the older Springs & Struts method. 

**Springs & Struts**

Set its frame to match your container view, then add the player view to the container view in your view hierarchy. Note that `videoContainer` is your own view object in your app's layout.

     self.playerView.frame = self.videoContainer.bounds;
     self.playerView.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;

**Auto Layout**

    self.playerView.translatesAutoresizingMaskIntoConstraints = NO;
    [NSLayoutConstraint activateConstraints:@[
                                              [self.playerView.topAnchor constraintEqualToAnchor:self.videoContainer.topAnchor],
                                              [self.playerView.rightAnchor constraintEqualToAnchor:self.videoContainer.rightAnchor],
                                              [self.playerView.leftAnchor constraintEqualToAnchor:self.videoContainer.leftAnchor],
                                              [self.playerView.bottomAnchor constraintEqualToAnchor:self.videoContainer.bottomAnchor],
                                              ]];

Now create the `BCOVPlaybackController`, assign it to your player view, and then start playing videos.

    // Initialize companion slots
    BCOVSSAIAdComponentDisplayContainer *displayContainer = [[BCOVSSAIAdComponentDisplayContainer alloc] initWithCompanionSlots:@[]];

    // Create the playback controller
    BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
    id<BCOVPlaybackController> playbackController = [sdkManager createSSAIPlaybackControllerWithViewStrategy:nil];

    // Listen for display/companion ad messages
    [playbackController addSessionConsumer:displayContainer];

	// Tell the player view this is the playback controller we're using
	self.playerView.playbackController = playbackController;
    
    // Create and play your video. For Unicorn Once-style VMAP URLs, create the BCOVVideo object directly.
    BCOVPlaybackService *playbackService = [[BCOVPlaybackService alloc] initWithAccountId:accoundId
                                                                                policyKey:policyKey];
    [playbackService findVideoWithVideoID:videoID
                               parameters:{ kBCOVPlaybackServiceParamaterKeyAdConfigId: <valid-ad-config-id> }
                               completion:^(BCOVVideo *video,
                                            NSDictionary *jsonResponse,
                                            NSError *error) {
    
                                 [playbackController setVideos:@[ video ]];
                                 [playbackController play];
    
                              }];

See the README in the BrightcovePlayerSDK for more details about how to use and customize the PlayerUI controls.

Access to VMAP Response Data
==========================
Should you want access to the VMAP response data you can subscribe to the `kBCOVSSAIVMAPResponseReceivedNotification` notification. Once received, the notification's userInfo dictionary will contain the VMAP response as NSData. You can use the `kBCOVSSAIVMAPResponseReceivedNotificationDataUserInfoKey` constant to access it from userInfo. Since you may have multiple playback controllers, and thus multiple VMAP responses, you can check the notification's object, `id playbackController = notification.object` to verify which video the VMAP data is for. Additionally, when you subscribe to the notification you can set a playback controller as the object so that only VMAP data notifications regarding that playback controller will be received. For example:

```
[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(vmapResponseReceived:) name:kBCOVSSAIVMAPResponseReceivedNotification object:self.playbackController];
```

Known Issues
==========================

* Because tvOS does not support Web browsing, Companion Ads, Learn More and all ad click throughs are ignored on that platform.

* You cannot use BrightcoveSSAI with any other Brightcove plugins except for the BrightcoveFairPlay plugin.

* If you want to use the BrightcoveSSAI plugin along with the BrightcoveFairPlay plugin then the BrightcoveFairPlay plugin must be the `upstreamSessionProvider` of the SSAI session provider.

* The SSAI plugin does not support playing SSAI content and non SSAI content in the same playback controller. If you need to play both, you need to create separate playback controllers.

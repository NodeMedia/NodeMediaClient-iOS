Pod::Spec.new do |spec|
  spec.name               = "NodeMediaClient"
  spec.version            = "3.2.7"
  spec.summary            = "A live streaming SDK."
  spec.description        = "NodeMedia RTMP/RTSP/HTTP Play/Publish Client SDK for iOS"
  spec.homepage           = "https://www.nodemedia.cn"
  spec.documentation_url  = "https://www.nodemedia.cn/doc/web/#/7?page_id=73"
  spec.license            = { :type => 'Copyright', :text => 'Copyright 2024 NodeMedia Ltd. All rights reserved.' }
  spec.author             = { "Chen Mingliang" => "illuspas@msn.com" }
  spec.readme             = 'https://raw.githubusercontent.com/NodeMedia/NodeMediaClient-iOS/master/README.md'
  spec.source             = { :git => 'https://github.com/NodeMedia/NodeMediaClient-iOS.git', :tag => "#{spec.version}" }
  spec.libraries          = 'z'
  spec.frameworks         = 'CoreMedia','AudioToolbox','VideoToolbox','AVFoundation'

  # Supported deployment targets
  spec.ios.deployment_target  = "12.0"

  # Published binaries
  spec.vendored_frameworks = "NodeMediaClient.xcframework"
end
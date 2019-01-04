
Pod::Spec.new do |s|
  s.name         = "RNThreerice"
  s.version      = "1.0.0"
  s.summary      = "RNThreerice"
  s.description  = <<-DESC
                  RNThreerice
                   DESC
  s.homepage     = ""
  s.license      = "MIT"
  # s.license      = { :type => "MIT", :file => "FILE_LICENSE" }
  s.author             = { "author" => "author@domain.cn" }
  s.platform     = :ios, "7.0"
  s.source       = { :git => "https://github.com/author/RNThreerice.git", :tag => "master" }
  s.source_files  = "RNThreerice/**/*.{h,m}"
  s.requires_arc = true


  s.dependency "React"
  #s.dependency "others"

end

  
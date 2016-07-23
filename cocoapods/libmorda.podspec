Pod::Spec.new do |s|
  s.name         = "libmorda"
  s.version      = "0.2.2"
  s.summary      = "C++ cross-platform GUI library."
  s.homepage     = "https://github.com/igagis/morda"
  s.license      = 'MIT'
  s.author       = { "Ivan Gagis" => "igagis@gmail.com" }
  s.platform     = :ios, "7.0"
  
  s.source = { :git => "https://github.com/igagis/morda.git", :tag => s.version }

  s.source_files  = "src/**/*.{hpp,h,cpp,inc}", "src/morda/glue/ios/main.mm", "src/soname.txt"
  s.header_mappings_dir = "src"

  s.xcconfig = { 'HEADER_SEARCH_PATHS' => '"${PODS_ROOT}/Headers/Private/freetype"' }

  s.compiler_flags = "-fno-objc-arc"

  s.dependency 'libutki', '>= 1.0.18'
  s.dependency 'libpogodi', '>= 1.0.8'
  s.dependency 'libpapki', '>= 1.0.11'
  s.dependency 'libnitki', '>= 1.0.8'
  s.dependency 'libkolme', '>= 1.0.6'
  s.dependency 'libstob', '>= 3.2.3'
  s.dependency 'libaika', '>= 1.0.7'
  s.dependency 'libpng_igagis', '>= 1.4.1'
  s.dependency 'freetype', '>= 2.6.4'
  s.dependency 'libjpeg', '>= 6.1.1'
  s.dependency 'libsvgren', '>= 0.3.13'
end
# frozen_string_literal: true

require_relative "lib/myhidapi/version"

Gem::Specification.new do |spec|
  spec.name = "myhidapi"
  spec.version = MyHIDAPI::VERSION
  spec.authors = ["Repy", "Aaron Patterson"]
  spec.email = ["gamecube02+git@gmail.com", "tenderlove@ruby-lang.org"]

  spec.summary = "A wrapper around hidapi for Ruby"
  spec.description = <<EOF
This is a small wrapper around HIDAPI.
I couldn't get other HIDAPI wrappers to work, so I wrote this one.
I'm using it to communicate with my keyboard, so it really only supports enough of the HIDAPI to do that.

This gem is a fork from the original work by Aaron Patterson (@tenderlove).
The original repository can be found at https://github.com/tenderlove/myhidapi.
EOF

  spec.licenses    = ['MIT']
  spec.homepage = "https://github.com/Repy/myhidapi"
  spec.required_ruby_version = ">= 3.2.0"

  spec.metadata["homepage_uri"] = spec.homepage
  spec.metadata["source_code_uri"] = "https://github.com/Repy/myhidapi"

  # Specify which files should be added to the gem when it is released.
  # The `git ls-files -z` loads the files in the RubyGem that have been added into git.
  gemspec = File.basename(__FILE__)
  spec.files = IO.popen(%w[git ls-files -z], chdir: __dir__, err: IO::NULL) do |ls|
    ls.readlines("\x0", chomp: true).reject do |f|
      (f == gemspec) ||
        f.start_with?(*%w[bin/ Gemfile .gitignore])
    end
  end
  spec.bindir = "exe"
  spec.executables = spec.files.grep(%r{\Aexe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]
  spec.extensions = ["ext/myhidapi/extconf.rb"]

end

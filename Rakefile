# frozen_string_literal: true

require "bundler/gem_tasks"
require "rake/extensiontask"
require 'rake/packagetask'

task build: :compile

GEMSPEC = Gem::Specification.load("myhidapi.gemspec")

Rake::ExtensionTask.new("myhidapi", GEMSPEC) do |ext|
  ext.lib_dir = "lib/myhidapi"
end

Gem::PackageTask.new(GEMSPEC) do |pkg|
end

task default: %i[clobber compile]

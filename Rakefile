# frozen_string_literal: true

require "bundler/gem_tasks"
require "rake/extensiontask"
require 'rake/packagetask'

task build: :compile

GEMSPEC = Gem::Specification.load("hidaping.gemspec")

Rake::ExtensionTask.new("hidaping", GEMSPEC) do |ext|
  ext.lib_dir = "lib/hidaping"
end

Gem::PackageTask.new(GEMSPEC) do |pkg|
end

task default: %i[clobber compile]

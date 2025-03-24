.PHONY: release build test
prepare: assets/scripts/prepare.sh
	@bash $<

update: assets/scripts/update.sh
	@bash $<

check: assets/scripts/check.sh
	@bash $<

resolve: assets/scripts/resolve.sh
	@bash $<


release:
	@cmake --preset=release
	@cmake --build release

build:
	@cmake --preset=test
	@cmake --build build

test:
	# for example: make run_test cases='ToString.*'
	# run all test: make run_test cases='*'
	@./build/tests/gtest_main --gtest_filter=$(cases)

test-all:
	@./build/tests/gtest_main --gtest_filter='*'


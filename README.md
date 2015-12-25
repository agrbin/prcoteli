# Programming Contest Template Library - PrCoTeLi

[Getting started](https://raw.githubusercontent.com/lukakalinovcic/prcoteli/master/doc/getting_started.md)

## Code health

This repo uses some of the Google code style conventions. Check the style with:

```
./run_lint.sh
```

If you are unhappy with the lint results, feel free to blacklist the lint
category in CPPLINT.cfg. We are using linter mostly to check that our include
guards are appropriate (unique).

To automatically solve most of the style violations, install clang-format and
run

```
clang-format -i $(find concepts/ impl/ testing/ -type f)
```

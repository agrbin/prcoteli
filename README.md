# Programming Contest Template Library - PrCoTeLi

[Getting started](https://raw.githubusercontent.com/lukakalinovcic/prcoteli/master/doc/getting_started.md)

## Code health

This repo uses Google-like code style.

```
wget https://raw.githubusercontent.com/google/styleguide/gh-pages/cpplint/cpplint.py
chmod +x cpplint.py
./cpplint.py --extensions=cc,h $(find impl/ concepts/ testing/ -type f)
```

To automatically solve most of the style violations, install clang-format and
run

```
clang-format -i $(find concepts/ impl/ testing/ -type f)
```

# C Lecture 3
식을 후위표기식으로 표현하기

## 목표
* 후위표기식을 이해한다.
* 스택을 활용하여 후위표기식을 만들 수 있다.

## 구현
파일의 내용을 읽어 후위 표기식으로 바꾸어 출력 하면 됩니다.
```
<file 10.in>
1. 1 + 2 - 3 * 4 / 5 + 6
```
```
$ ./run testcases/10.in
1 2 + 3 4 * 5 / - 6 +
```

## 기한
2018-07-12
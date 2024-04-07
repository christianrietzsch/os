int count_digits(int n) {
  if(n == 0) {return 1;}
  int length = 0;
  //rewrite: 123/1000 >= 1 more operations than 123 < 1000
  for(int i = 1; n/i >= 1 || n/i <= -1; i *= 10) {length++;}
  return length;
}

int pow(int base, int power)
{
  if(power == 0) {return 0;}
  if(power == 1) {return base;}
  int result = base;
  for(int i = 2; i <= power; i++) {result *= base;}
  return result;
}

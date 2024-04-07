int search_char(char* str, char chr, int start_pos)
{
  //-1 error code
  for(int i = start_pos; str[i] != '\0'; i++)
  {
    if(str[i] == chr) {return i;}
  }
  return -1;
}

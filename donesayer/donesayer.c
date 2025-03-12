#include <stdio.h>
#include <stdlib.h>

char *quotes[13] = {
  "There are three states of being. Not knowing, action and completion.\n",
  "Accept that everything is a draft. It helps to get it done.\n",
  "There is no editing stage.\n",
  "Pretending you know what you’re doing is almost the same as knowing what you are doing, so just accept that you know what you’re doing even if you don’t and do it.\n",
  "Banish procrastination. If you wait more than a week to get an idea done, abandon it.\n",
  "The point of being done is not to finish but to get other things done.\n",
  "Once you’re done you can throw it away.\n",
  "Laugh at perfection. It’s boring and keeps you from being done.\n",
  "People without dirty hands are wrong. Doing something makes you right.\n",
  "Failure counts as done. So do mistakes.\n",
  "Destruction is a variant of done.\n",
  "If you have an idea and publish it on the internet, that counts as a ghost of done.\n",
  "Done is the engine of more.\n"
};



int main (int argc, char **argv){
  if (argc == 1){
    printf("call with the index of the cult of done manifesto quote you want\n");
    return -1;
  }
  unsigned int index = atoi (argv[1]);

  if (index < 0 || index > 12){
    printf("there are 13 quotes, 0 indexed\n");
    return -1;
  }

  printf("%s", quotes[index]);
}

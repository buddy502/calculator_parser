#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 64
#define BUFFER_ITEMS 32

typedef enum {
   OK,
   PARSE_ERR,
   INVALID_FORMAT
}ERR_VAL;

typedef struct {
   uint8_t ret_val;
   ERR_VAL err;
}int_err;

typedef struct {
   char arr[BUFFER_ITEMS][BUFFER_SIZE];
   size_t count;
} DoublyStackStr;

// idx == number eg num[0] == 0 num[1] == 1
const uint8_t NUMBERS[10] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57};

// SYMBOLS
const uint8_t add_symbol = 43;
const uint8_t sub_symbol = 45;
const uint8_t mul_symbol = 42;
const uint8_t div_symbol = 47;
// -----------------

void push_top(DoublyStackStr *stack, const char *value) {
    if (stack->count >= BUFFER_ITEMS) return;
    snprintf(stack->arr[stack->count], BUFFER_SIZE, "%s", value);
    stack->count++;
}

void push_bottom() {
}

char* trim_whitespace(char* str) {
   if(str[0] == '\0') return str;
   size_t str_idx = 0;

   for (size_t i = 0; str[i] != '\0'; ++i) {
      if(!isspace(str[str_idx])) {
         str[str_idx++] = str[i];
      }
   }
   str[str_idx] = '\0';
   return str;
}

// handles case of user typing '\0'
bool string_isnum(char* text, uint8_t text_len) {
   for(uint8_t i = 0; i < text_len; ++i) {
      if (isdigit(text[i])) {
         return false;
      }
   }
   return true;
}

int_err calculator(char* text, uint8_t text_len) {
   if (!string_isnum(text, text_len)) {
      return (int_err){0, PARSE_ERR};
   }

   if (strchr("+-*/", text[0])) {
      return (int_err){0, INVALID_FORMAT};
   }

   // brute force isn't that expensive but it's boring ngl
   // initial problem: A brute force would be to iterate in PEMDAS order
   // Find every case of mul / div
   // Possible solution:
   // Have an array of strings that each have 2 digits and a symbol
   // if a string doesn't have that, return INVALID_FORMAT
   // 1+32 = cur_str
   // 32*3 = cur_str
   // 1+32*3/3+2/8
   //    ^
   // syb_arr = [+, *, /, +, /]
   // Possible Solution:
   // Create a stack of precedence where you iterate through the string
   // 1 time but push operations on the bottom or top depending on precedence
   // str_stack.push_bottom("1+32"), str_stack.push_top("32*3")
   // then pop from the top of the stack and perform the operation on each one

   // build while iterating
   char full_cur_num[] = "";
   for(uint8_t i = 1; i < text_len; ++i) {
      // if a symbol appears 2 times error
      if (strchr("+-*/", text[i-1]) && strchr("+-*/", text[i])) {
         return (int_err){0, INVALID_FORMAT};
      }
      // get to symbol then refresh
      // PROBABLY USE LATER
      //if (strchr("+-*/", text[i])) full_cur_num[0] = '\0';

      // !!! IMPORTANT PEMDAS ORDER
      // Parse Parenthesis
      printf("Parse Parenthesis Unimplemented");

      // Multiplication

      // Division

      // Addition

      // Subtraction
      

   }

   // returing OK and 0 for now
   // later return OK and (value) instead
   return (int_err){0, OK};
}

int main(void) {
   char buffer[BUFFER_SIZE];
   fgets(buffer, sizeof(buffer), stdin);
   // buffer = text 

   trim_whitespace(buffer);

   //calculator(buffer);
}

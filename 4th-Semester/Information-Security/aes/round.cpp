#include "round.h"

matrix plaintext;
matrix ciphertext;
matrix key;
word* expanded_key;

void take_input(){ //convert input into matrix and store it in global variables.
  byte byte_input[16], byte_key[16];
  printf("Enter Input: ");
  for(int i=0 ;i<16; i++) scanf("%x ",&byte_input[i]);
  printf("Enter key: ");
  for(int i=0 ;i<16; i++) scanf("%x ",&byte_key[i]);

  plaintext.make_matrix(byte_input);
  ciphertext.make_matrix(byte_input);
  key.make_matrix(byte_key);

  expanded_key = key_expansion_algorithm(byte_key);
}


void round(int round_number){ //changes the global variable
  matrix round_key;

  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      round_key.storage[j][i] = expanded_key[round_number*4+i].storage[j];
    }
  }

  // printf("Round key for round %d:\n",round_number);
  // round_key.print();
  if(round_number==0){
    ciphertext.add_round_key(round_key);
  }else if(round_number==10){
    ciphertext.substitute();
    ciphertext.shift_rows();
    ciphertext.add_round_key(round_key);
 }else{
  ciphertext.substitute();
    ciphertext.shift_rows();
    ciphertext.multiply_with_mix_column_matrix();
    ciphertext.add_round_key(round_key);

 }
}

void inverse_round(int round_number){ //changes the global variable
  matrix round_key;
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      round_key.storage[j][i] = expanded_key[40-round_number*4+i].storage[j];
    }
  }
  
  //printf("Round key for reverse round %d:\n",round_number);
  //round_key.print();
  if(round_number==0){
    ciphertext.add_round_key(round_key);
  }
  else if(round_number==10){
    ciphertext.inverse_shift_rows();
    ciphertext.inverse_substitute();
    ciphertext.add_round_key(round_key);
  }
  else{
    ciphertext.inverse_shift_rows();
    ciphertext.inverse_substitute();
    ciphertext.add_round_key(round_key);
    ciphertext.multiply_with_inverse_mix_column_matrix();
  }
}

void encryption_algorithm(){
  for(int rnd=0; rnd<=10; rnd++) round(rnd);
}

void decryption_algorithm(){
  for(int rnd=0; rnd<=10; rnd++) inverse_round(rnd);
}

void test_round(){
  printf("Testing round module: -------------");
  take_input();
  printf("Plaintext: \n");
  plaintext.print();
  printf("Key: \n");
  key.print();

  int r=1;

  round(r);
  printf("Ciphertext after round %d: \n",r);
  ciphertext.print();

  // inverse_round(10-r);
  // inverse_round(r);
  printf("Reverse Ciphertext after round %d: \n",10-r);
  ciphertext.print();
}

void test_aes(){
  take_input();
  printf("Plaintext:\n");
  plaintext.print();
  encryption_algorithm();
  printf("Ciphertext:\n");
  ciphertext.print();
  decryption_algorithm();
  printf("Reverse Ciphertext:\n");
  ciphertext.print();
}
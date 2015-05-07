void setup()
{
}
void loop()
{
  int m = 32;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < m; j++) {
      if (i == 0) {
        led(D0, (m - j), j, 0);
      }
      else if (i == 1) {
        led(D0, 0, (m - j), j);
      }
      else {
        led(D0, j, 0, (m - j));
      }
      delay(100);
    }
  }
}
void led(int pin, int r, int g, int b) {
  int bufBin[24];
  for (int i = 0; i < 3; i++) {
    int v = (i == 0) ? g : (i == 1) ? r : b;
    v = (v > 255) ? 255 : (v < 0) ? 0 : v;
    for (int j = 0; j < 8; j++) {
      bufBin[i * 8 + j] = (((v >> (7 - j)) & 1) == 1) ? 1 : 0;
    }
  }

  const uint8_t pin_num = Pin_nRF51822_to_Arduino(pin);
  nrf_gpio_cfg_output(pin_num);
  const uint32_t MASK =  1 << pin_num;
  noInterrupts();
  NRF_GPIO->OUTCLR = (MASK);
  delayMicroseconds(100);
  for (int i = 0; i < 24; i++) {
    if (bufBin[i] == 1)
    {
      NRF_GPIO->OUTSET = (MASK);
      __ASM ( \
              " NOP\n\t" \
              " NOP\n\t" \
              " NOP\n\t" \
              " NOP\n\t" \
              " NOP\n\t" \
              " NOP\n\t" \
              " NOP\n\t" \
              " NOP\n\t" \
              " NOP\n\t" \
            );
      NRF_GPIO->OUTCLR = (MASK);
    }
    else	{
      NRF_GPIO->OUTSET = (MASK);
      __ASM (  \
               " NOP\n\t"  \
            );
      NRF_GPIO->OUTCLR = (MASK);
      __ASM ( \
              " NOP\n\t" \
              " NOP\n\t" \
              " NOP\n\t" \
              " NOP\n\t" \
              " NOP\n\t" \
              " NOP\n\t" \
              " NOP\n\t" \
              " NOP\n\t" \
            );
    }
  }
  delayMicroseconds(100);
  interrupts();
}

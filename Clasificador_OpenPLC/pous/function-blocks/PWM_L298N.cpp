(* PWM al pin ENA del L298N (GPIO21) con el mismo esquema del sketch de prueba: ledcAttach(pin, 5000, 8) y ledcWrite(pin, velocidad). *)

FUNCTION_BLOCK PWM_L298N
  VAR_INPUT
    Velocidad : INT; (* 0-255, igual que ledcWrite(ENB, velocidadActual) del sketch *)
  END_VAR
// PWM al pin ENA del L298N, igual que el sketch de prueba del equipo:
//   ledcAttach(ENB, 5000, 8);  ledcWrite(ENB, velocidadActual);
// La rampa se calcula en LADDER (rungs 34-36); este bloque solo escribe el PWM.
// GPIO21 sigue siendo el pin ENA de la tabla del Paso 1: al hacer ledcAttach el
// periferico LEDC toma el pin, y la escritura digital de Motor_Enable (%QX0.2) sobre
// GPIO21 deja de tener efecto (el PWM ya vale 0 cuando Motor_Enable = FALSE).

static const uint8_t  PWM_L298N_PIN  = 21;    // GPIO21 = ENA del L298N
static const uint32_t PWM_L298N_FREQ = 5000;  // Hz, igual que el sketch
static const uint8_t  PWM_L298N_BITS = 8;     // 0-255, igual que el sketch

void setup()
{
    ledcAttach(PWM_L298N_PIN, PWM_L298N_FREQ, PWM_L298N_BITS);
    ledcWrite(PWM_L298N_PIN, 0);
}

void loop()
{
    int v = Velocidad;
    if (v < 0) v = 0;
    if (v > 255) v = 255;
    ledcWrite(PWM_L298N_PIN, (uint32_t)v);
}

END_FUNCTION_BLOCK
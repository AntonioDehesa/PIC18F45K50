//These pins should be declared based on the PORTS you are using. For reference, check the image
//All credits to the original authors, i only translated it. https://programmazionemicro.altervista.org/5-progetto-pic18f45k50-display-lcd/
#define RS PORTAbits.RA0
#define EN PORTAbits.RA1
#define D4 PORTAbits.RA2
#define D5 PORTAbits.RA3
#define D6 PORTAbits.RA4
#define D7 PORTAbits.RA5
void LCD_PORT(unsigned char a);
void LCD_WriteCommand(unsigned char Command);
void LCD_Display(unsigned char State, unsigned char Cursor, unsigned char FlashingCursor);
void InitializeLCD(void);
void LCD_Clear(void);
void LCD_Cursor(unsigned char Line, unsigned char Column);
void LCD_ShowCharacter(unsigned char Character);
void LCD_ShowString(const unsigned char *String);
void LCD_ShowFloat(float Number);
void LCD_PORT(unsigned char a)
{
    if ((a & 1) == 1)
        D4 = 1;
    else
        D4 = 0;
    if ((a & 2) == 2)
        D5 = 1;
    else
        D5 = 0;
    if ((a & 4) == 4)
        D6 = 1;
    else
        D6 = 0;
    if ((a & 8) == 8)
        D7 = 1;
    else
        D7 = 0;
}

void LCD_WriteCommand(unsigned char Command)
{
    RS = 0;
    LCD_PORT(Command);
    EN = 1;
    __delay_ms(4);
    EN = 0;
}

/*void LCD_Display(unsigned char State, unsigned char Cursor, unsigned char FlashingCursor)
{
    LCD_WriteCommand(0x00);
    unsigned char Command = 0x08 | State << 2 | Cursor << 1 | FlashingCursor;
    LCD_WriteCommand(Command);
}*/

void InitializeLCD(void)
{
    // Method to initialize the display (datasheet)
    LCD_PORT(0x00);
    __delay_ms(20);
    LCD_WriteCommand(0x03);
    __delay_ms(10);
    LCD_WriteCommand(0x03);
    __delay_ms(10);
    LCD_WriteCommand(0x03);
    // Using 4 bits
    LCD_WriteCommand(0x02);
    // Display OFF
    LCD_WriteCommand(0x02);
    LCD_WriteCommand(0x08);
    // Display CLEAR
    LCD_WriteCommand(0x00);
    LCD_WriteCommand(0x0C);
    
    LCD_WriteCommand(0x00);
    LCD_WriteCommand(0x06);
}

void LCD_Clear(void)
{
    LCD_WriteCommand(0x00);
    LCD_WriteCommand(0x01);
}

void LCD_Cursor(unsigned char Line, unsigned char Column)
{
    unsigned char Dato;
    if (Line == 1)
    {
        Dato = 0x80 | Column - 1;
        LCD_WriteCommand(Dato >> 4);
        LCD_WriteCommand(Dato & 0x0F);
    }
    if (Line == 2)
    {
        Dato = 0xC0 | Column - 1;
        LCD_WriteCommand(Dato >> 4);
        LCD_WriteCommand(Dato & 0x0F);
    }
}

void LCD_ShowCharacter(unsigned char Character)
{
    RS = 1;
    LCD_PORT(Character >> 4);
    EN = 1;
    __delay_us(40);
    EN = 0;
    LCD_PORT(Character & 0x0F);
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void LCD_ShowString(const unsigned char *String)
{
    for (unsigned char i = 0; String[i] != '\0'; i++)
        LCD_ShowCharacter(String[i]);
}

/*void LCD_ShowInteger(int Numero)
{
    char Buffer[16];
    sprintf(Buffer, "%i", Numero);
    LCD_ShowString(Buffer);
}

void LCD_ShowDouble(double Number)
{
    char Buffer[16];
    sprintf(Buffer, "%.3f", Number);
    LCD_ShowString(Buffer);
}*/

void LCD_ShowFloat(float Number)
{
    char Buffer[16];
    sprintf(Buffer, "%.3f", Number);
    LCD_ShowString(Buffer);
}

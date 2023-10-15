
void all_retour(int *retour, int *status) 
{
        if ((*status & 0xFF) == 0)
            *retour = (*status >> 8) & 0xFF;
}

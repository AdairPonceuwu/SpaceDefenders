#ifndef ENEMY_H
#define ENEMY_H


class Enemy
{
    public:
        Enemy(float x, float y, float z, float angulo);
        Enemy();
        virtual ~Enemy();
        float enemy_radio = .45f;
        float enemigo_velocidad = .00015f;
        float V[3];
        bool condicion; // true vivo, false muerto
        float angulo;
        void updateEnemy(float angulo);
        void muerto();
    protected:

    private:
};

#endif // ENEMY_H

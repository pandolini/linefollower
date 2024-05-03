
#ifndef LOGIC_HPP
#define LOGIC_HPP

class Logic {
public:
    Logic(float Kp, float Kd, float Ki, float outputGain);
    short computeCourseCorrection(unsigned short currentLinePosition);
    void resetErrors();

    void setKp(float Kp) { Kp_ = Kp; }
    void setKd(float Kd) { Kd_ = Kd; }
    void setKi(float Ki) { Ki_ = Ki; }
    float getKp() const { return Kp_; }
    float getKd() const { return Kd_; }
    float getKi() const { return Ki_; }

private:
    unsigned short previousLinePosition_;
    const unsigned short desiredLinePosition_;
    short proportionalError_;
    short derivativeError_;
    short integralError_;
    short controlOutput_;
    float Kp_;
    float Kd_;
    float Ki_;
    float outputGain_;
};

#endif
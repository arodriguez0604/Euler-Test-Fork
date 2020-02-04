#pragma once

//#include <string>
#include <frc/WPILib.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
#include <frc/Servo.h>
#include "frc/smartdashboard/SmartDashboard.h"
#include <AHRS.h>
#include <math.h>

#define servoOpen     180
#define servoMid      90
#define servoClosed   0

using namespace frc;
using namespace rev;

bool driveMode = false;
bool limitSwitchBool = false;

class Robot : public TimedRobot {
  public:
    void RobotInit() override;
    void RobotPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void TestPeriodic() override;
    double ToPie(int degrees);
    double DeadZone(double speed, double zone);

    const int TALON = 5, SPARK = 7, SERVO = 0, POT = 0, LIMITSWITCH = 0;

  private:
    rev::CANSparkMax *spark;
    rev::CANEncoder *sparkEncoder;
    WPI_TalonSRX *talon;
    DigitalInput *limitSwitch;
    Servo *servo;
    AnalogPotentiometer *pot;
    XboxController *xbox;
};

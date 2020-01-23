#pragma once

#include <string>
#include <frc/WPILib.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
#include <frc/Servo.h>
#include "frc/smartdashboard/SmartDashboard.h"
#include <AHRS.h>

#define servoOpen     90
#define servoClosed   125

using namespace frc;
using namespace rev;

class Robot : public TimedRobot {
  public:
    void RobotInit() override;
    void RobotPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void TestPeriodic() override;
    double DeadZone(double speed, double zone);

    const int TALON = 5, SPARK = 7, SERVO = 0, POT = 9;

  private:
    rev::CANSparkMax *spark;
    rev::CANEncoder *sparkEncoder;
    WPI_TalonSRX *talon;
    Servo *servo;
    AnalogPotentiometer *pot;
    XboxController *xbox;
};

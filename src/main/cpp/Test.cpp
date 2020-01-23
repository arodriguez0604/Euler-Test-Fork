#include <iostream>
#include "Test.h"

void Robot::RobotInit() {   
    xbox         = new frc::XboxController(0);
    spark        = new CANSparkMax(SPARK, CANSparkMax::MotorType::kBrushless);
    talon        = new WPI_TalonSRX(TALON);
    servo        = new Servo(SERVO);
    pot          = new AnalogPotentiometer(POT, 1.0, 0.0);
    sparkEncoder = new CANEncoder(*spark);
}

void Robot::RobotPeriodic()  {
    TeleopPeriodic();
}

void Robot::AutonomousInit() {
    TeleopInit();
}

void Robot::AutonomousPeriodic() {
    
}

void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {
    spark->Set(DeadZone(xbox->GetY(GenericHID::JoystickHand::kLeftHand), .25));
    talon->Set(DeadZone(xbox->GetY(GenericHID::JoystickHand::kRightHand), .25));
    if (xbox->GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand) > .1) {
        servo->SetAngle(servoOpen);
    } else {
        servo->SetAngle(servoClosed);
    }

}

void Robot::TestPeriodic() {
    TeleopPeriodic();
}

double Robot::DeadZone(double speed, double zone) {
    if (abs(speed) < zone) {
        return 0;
    }
    return speed;
}

#ifndef RUNNING_FRC_TESTS
int main()  { 
  return frc::StartRobot<Robot>();
}
#endif
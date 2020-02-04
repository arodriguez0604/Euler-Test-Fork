#include "Test.h"

void Robot::RobotInit() {   
    xbox         = new frc::XboxController(0);
    spark        = new CANSparkMax(SPARK, CANSparkMax::MotorType::kBrushless);
    talon        = new WPI_TalonSRX(TALON);
    limitSwitch  = new DigitalInput(LIMITSWITCH);
    servo        = new Servo(SERVO);
    pot          = new AnalogPotentiometer(POT, 360, 0.0);
    sparkEncoder = new CANEncoder(*spark);
}

void Robot::RobotPeriodic()  {
    TeleopPeriodic();
}

void Robot::AutonomousInit() {
    TeleopInit();
}

void Robot::AutonomousPeriodic() {
    talon->Set(.5);
    spark->Set(.5);
}

void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {
    if (xbox->GetYButtonPressed())
        driveMode = !driveMode;

    if (limitSwitch->Get())
        limitSwitchBool = !limitSwitchBool;
    
    SmartDashboard::PutBoolean ("Limit Switch Variable", limitSwitch);

    if (!driveMode) {
        if (xbox->GetStickButton(GenericHID::JoystickHand::kRightHand)) {
            servo->SetAngle(servoMid);
            SmartDashboard::PutBoolean ("Servo Middle", true);
            if (xbox->GetStickButton(GenericHID::JoystickHand::kLeftHand)) {
                servo->SetAngle(servoOpen);
                SmartDashboard::PutBoolean ("Servo Open", true);
                SmartDashboard::PutBoolean ("Servo Middle", false);
            } else {
                SmartDashboard::PutBoolean ("Servo Open", false);
              }

        } else {
            servo->SetAngle(servoClosed);
            SmartDashboard::PutBoolean ("Servo Open", false);
            SmartDashboard::PutBoolean ("Servo Middle", false);
          }
    } else {
        if (!(limitSwitch->Get())) {
            if (xbox->GetBumper(GenericHID::JoystickHand::kLeftHand)) {
                spark->Set(DeadZone(xbox->GetY(GenericHID::JoystickHand::kLeftHand), .25) / 2.0);
                talon->Set(DeadZone(xbox->GetY(GenericHID::JoystickHand::kRightHand), .25) / 2.0);
            } else if (xbox->GetBumper(GenericHID::JoystickHand::kRightHand)) {
                spark->Set(DeadZone(xbox->GetY(GenericHID::JoystickHand::kLeftHand), .25) / 10.0);
                talon->Set(DeadZone(xbox->GetY(GenericHID::JoystickHand::kRightHand), .25) / 10.0);
                } else {
                    spark->Set(DeadZone(xbox->GetY(GenericHID::JoystickHand::kLeftHand), .25));
                    talon->Set(DeadZone(xbox->GetY(GenericHID::JoystickHand::kRightHand), .25));
                  }
        } else {
            spark->Set(0);
            talon->Set(0);
          }
      }

    SmartDashboard::PutNumber  ("Servo Angle", servo->GetAngle());
    SmartDashboard::PutBoolean ("Drive Mode", driveMode);
    SmartDashboard::PutBoolean ("Limit Switch On", limitSwitchBool);
    SmartDashboard::PutNumber  ("Potentiometer Angle", ToPie(pot->Get()));
    SmartDashboard::PutBoolean ("Limit Switch", limitSwitch->Get());
    //SmartDashboard::PutNumber ("Talon Speed", talon->GetVelocity());
    SmartDashboard::PutNumber  ("Spark Max Speed", sparkEncoder->GetVelocity());
    SmartDashboard::PutNumber  ("Y - Axis (Left)", xbox->GetY(GenericHID::JoystickHand::kLeftHand));
    SmartDashboard::PutNumber  ("X - Axis (Left)", xbox->GetX(GenericHID::JoystickHand::kLeftHand));
    SmartDashboard::PutNumber  ("Y - Axis (Right)", xbox->GetY(GenericHID::JoystickHand::kRightHand));
    SmartDashboard::PutNumber  ("X - Axis (Right)", xbox->GetX(GenericHID::JoystickHand::kRightHand));

}

void Robot::TestPeriodic() {
    TeleopPeriodic();
}

double Robot::ToPie (int degrees) {
    return (degrees / 180) * M_PI;
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
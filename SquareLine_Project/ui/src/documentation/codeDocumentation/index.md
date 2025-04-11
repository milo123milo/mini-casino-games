# Casino Games Technical Documentation

## Documentation Index

Welcome to the technical documentation for the Casino Games application. This comprehensive guide is designed to help developers understand, maintain, and extend the codebase.

### Getting Started

- [Project Overview](./project-overview.md) - High-level introduction to the project structure and architecture
- [Deployment Guide](./deployment-guide.md) - Instructions for building and deploying the application with Arduino IDE

### System Architecture

- [UI System](./ui-system.md) - Documentation of the user interface implementation using LVGL
- [Animation System](./animation-system.md) - Guide to the animation framework and implementations
- [Store System](./store-system.md) - Documentation of the in-game economy and state management
- [Audio System](./audio-system.md) - Documentation of the DFPlayer-based sound system

### Game Implementations

- [Game Implementations](./game-implementations.md) - Technical details of each game implementation
  - Slots Game
  - Dice Roll Game
  - Blackjack Game

### Reference and Support

- [Troubleshooting Guide](./troubleshooting-guide.md) - Common issues and their solutions

### Game Rules and Logic
 
- [Game Rules](../gameRules/index.md) - Detailed explanation of game rules and payout structures
  - [Slots](../gameRules/slots.md)
  - [Dice](../gameRules/dice.md)
  - [Blackjack](../gameRules/blackjack.md)

## Quick References

### Key Component Dependencies

```
Arduino Framework → TFT_eSPI → LVGL → UI System → Animation System → Game Logic → Store System
                   DFPlayer  → Audio System ↗
```

### Directory Structure

- `ui/src/` - Main source code
  - `ui/src/ui/` - Generated UI code
  - `ui/src/games/` - Game implementations
  - `ui/src/store/` - Store system
  - `ui/src/assets/` - Images and resources
  - `ui/src/documentation/` - Documentation files
- `Casino_Games.ino` - Main Arduino sketch file

### Arduino Libraries Required

- ESP32 Board Package (v2.0.11)
- LVGL (v8.x)
- TFT_eSPI
- DFRobotDFPlayerMini (optional for audio)

### Development Workflow

1. Design UI components in SquareLine Studio
2. Export UI to the project
3. Implement game logic and event handlers
4. Configure Arduino environment and required libraries
5. Compile and upload with Arduino IDE
6. Test on target hardware
7. Update documentation as needed

## Contributing to Documentation

When updating or extending this documentation:

1. Keep individual documents focused on a single aspect
2. Update this index when adding new documentation files
3. Ensure code examples are accurate and up-to-date
4. Add diagrams where they help clarify concepts

## Revision History

- **Initial Documentation**: Creation of comprehensive documentation structure
- **v1.0**: First complete documentation set
- **v1.1**: Updated for Arduino IDE deployment and DFPlayer audio integration

---

*For any questions or suggestions regarding this documentation, please contact the development team.* 
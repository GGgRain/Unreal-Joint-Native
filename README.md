<div align="center">
  <img src="https://github.com/user-attachments/assets/30601e49-3fe1-48d9-ac61-f5b3818c0eff" width="300" height="300" alt="Joint-Native Logo">
</div>

<div align="center">
  <h1>Joint-Native</h1>
  <h3>Official Extension Plugin for Joint - for Highly Customizable Advanced Narrative System</h3>
</div>

<p align="center">
  <a href="https://github.com/GGgRain/Unreal-Joint-Native/fork" target="_blank">
    <img src="https://img.shields.io/github/forks/GGgRain/Unreal-Joint-Native?" alt="Badge showing the total of project forks">
  </a>
  <a href="https://github.com/GGgRain/Unreal-Joint-Native/stargazers" target="_blank">
    <img src="https://img.shields.io/github/stars/GGgRain/Unreal-Joint-Native?" alt="Badge showing the total of project stars">
  </a>
  <a href="https://github.com/GGgRain/Unreal-Joint-Native/blob/master/LICENSE" target="_blank">
    <img alt="Badge showing project license type" src="https://img.shields.io/github/license/GGgRain/Unreal-Joint-Native?color=f85149">
  </a>
  <a href="https://discord.gg/DzNFax2aBS">
    <img src="https://img.shields.io/discord/977755047557496882?logo=discord&logoColor=white" alt="Chat on Discord">
  </a>
</p>

<p align="center">
  <a href="#mag-about">About</a> &#xa0; | &#xa0;
  <a href="#clipboard-dependencies">Dependencies</a> &#xa0; | &#xa0;
  <a href="#inbox_tray-installation">Installation</a> &#xa0; | &#xa0;
  <a href="#camera-usecases">Usecases</a> &#xa0; | &#xa0;
  <a href="#loudspeaker-supports">Supports</a> &#xa0; | &#xa0;
  <a href="#memo-license">License</a>
</p>

## :mag: About ##

Joint-Native is the official extension plugin that extends [Joint](https://github.com/GGgRain/Unreal-Joint) by providing essential nodes, widgets, sample levels, and assets designed for creating various conversation scripting systems within Unreal Engine. This plugin is essential for developers aiming to implement conversation-based interactions and functionality efficiently.

The Dialogue System provided in this Git repository is an advanced tool designed to empower developers and storytellers to create highly customizable and dynamic narrative experiences. It supports a wide range of applications, from simple dialogues to complex, interactive storytelling systems inspired by games like Hogwarts Legacy or The Witcher 3. The system offers maximum control over participants, events, and the surrounding world, enabling intricate narrative designs.

<p align="center">
  <i>Please consider leaving a star if you loved this project! </i>⭐
</p>

## :clipboard: Dependencies ##

This plugin relies on the [Joint](https://www.unrealengine.com/marketplace/ko/product/ec432b9261c94b70a4068507d42a4f5a) plugin. Ensure that you’ve installed Joint into your project before proceeding with the installation of Joint-Native.

## :inbox_tray: Installation & Necessary Setting Up ##

### Steps:
1. Download [Joint](https://github.com/GGgRain/Unreal-Joint) on your project. Follow the description on the GitHub repository. (Now it's free to install!!)
2. Download this repository as a zip file or clone it to your workstation, then unzip the folder and rename it to `Joint-Native`.
3. Place the unzipped `Joint-Native` folder into the `Plugins` directory of your Unreal project. If this directory doesn’t exist, create it.
4. Launch your project and confirm it runs successfully. If you see a prompt asking about building modules, click **Yes**.
5. **In editor, go visit Project Settings -> GameplayTags -> Add an element on Gameplay Tag Table List -> Provide DT_JointSampleGameplayTags**
6. If the plugin doesn’t launch properly, please review the installation steps again. For further assistance, reach out to us on [Discord](https://discord.gg/DzNFax2aBS).

> [!TIP] 
> Check this out, especially if you've never compiled or used C++ code on your Unreal Engine before:
> If the plugin doesn’t launch properly, you may check your machine's Visual Studio configuration for the C++ code build to be valid. Please make sure to follow these steps:
> 
> In your Visual Studio configuration (you can modify it in Visual Studio Installer) :
> * Click Modify on the 2022 version
> * Go to Individual components
> * Type “MSVC” in the search bar
> * Check “MSVC v143 - VS 2022 C++ x64/86 build tools (v14.38-17.8)”
> * Then click modify in the bottom right corner
>
> Second, You have to install **Game development with C++** workload as well.
> 
> ![vs2022_workloads_game_development](https://github.com/user-attachments/assets/6465a82e-ffc9-4dbd-bda4-86c30b0a83c1)
>
> Big thanks to "Kieran" - who posted the fix for the issue on the forum. 
> 
> Original Post: https://forums.unrealengine.com/t/help-visual-studio-preferred-version-in-5-4/2001249


Once installed and launched, be sure to review the **README** asset for more detailed information.

## :camera: Usecases ##

This plugin can be utilized to create detailed conversation systems using nodes and widgets within Unreal Engine. Check out the provided sample level to understand how to integrate and utilize these features in your project.

![Nodes](https://github.com/GGgRain/Unreal-Joint-Native/assets/69423737/470095f4-9af4-435f-a766-b546b8eb69f6)
![Sample](https://github.com/GGgRain/Unreal-Joint-Native/assets/69423737/c313cb70-8f13-455e-80a0-6323adb58833)
![Sample Level](https://github.com/GGgRain/Unreal-Joint-Native/assets/69423737/f779d7aa-648a-44b9-9bef-6534afd6341c)

## :loudspeaker: Supports ##

If you need help, feel free to join our [official Discord support channel](https://discord.gg/DzNFax2aBS). Our community is happy to assist you with any plugin-related queries.

## :memo: License ##

This project is licensed under the [Apache License 2.0](https://www.apache.org/licenses/LICENSE-2.0). Please refer to the [LICENSE](LICENSE) file for further details.

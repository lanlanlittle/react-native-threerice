
# react-native-threerice

## Getting started

`$ npm install react-native-threerice --save`

### Mostly automatic installation

`$ react-native link react-native-threerice`

### Manual installation


#### iOS

1. In XCode, in the project navigator, right click `Libraries` ➜ `Add Files to [your project's name]`
2. Go to `node_modules` ➜ `react-native-threerice` and add `RNThreerice.xcodeproj`
3. In XCode, in the project navigator, select your project. Add `libRNThreerice.a` to your project's `Build Phases` ➜ `Link Binary With Libraries`
4. Run your project (`Cmd+R`)<

#### Android

1. Open up `android/app/src/main/java/[...]/MainActivity.java`
  - Add `import com.zxx.three.rice.RNThreericePackage;` to the imports at the top of the file
  - Add `new RNThreericePackage()` to the list returned by the `getPackages()` method
2. Append the following lines to `android/settings.gradle`:
  	```
  	include ':react-native-threerice'
  	project(':react-native-threerice').projectDir = new File(rootProject.projectDir, 	'../node_modules/react-native-threerice/android')
  	```
3. Insert the following lines inside the dependencies block in `android/app/build.gradle`:
  	```
      compile project(':react-native-threerice')
  	```


## Usage
```javascript
import RNThreerice from 'react-native-threerice';

// TODO: What to do with the module?
RNThreerice;
```
  
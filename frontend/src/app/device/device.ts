import { Component, input } from '@angular/core';
import { Service } from '../service/service';

@Component({
  selector: 'app-device',
  imports: [Service],
  templateUrl: './device.html',
  styleUrl: './device.css',
})
export class Device {
  ip = input<string>();
}

import { Component, input, output } from '@angular/core';
import { Service } from '../service/service';
import { IService } from '../interfaces/IService';
import { IPosition } from '../interfaces/IPosition';
import { CdkDrag } from "@angular/cdk/drag-drop";

@Component({
  selector: 'app-device',
  imports: [Service, CdkDrag],
  templateUrl: './device.html',
  styleUrl: './device.css',
})
export class Device {
  ip = input<string>("unknown");
  mac = input<string>("unknown");
  hostname = input<string>("unknown");
  status = input<string>("Unknown");
  services = input<Array<IService>>([]);
  position = output<IPosition>();
}

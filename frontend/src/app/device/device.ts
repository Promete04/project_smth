import { Component, input } from '@angular/core';
import { Service, IService } from '../service/service';
import { CdkDrag } from "@angular/cdk/drag-drop";

@Component({
  selector: 'app-device',
  imports: [Service, CdkDrag],
  templateUrl: './device.html',
  styleUrl: './device.css',
})
export class Device {
  ip = input<string>();
  services: Array<IService> = [
    {"port": 80, "name": "web server", "status": "active"}
  ];
  x = input<number>();
  y = input<number>();
}

import { Component, input } from '@angular/core';
import { Service } from '../service/service';
import { IService } from '../interfaces/IService';
import { CdkDrag } from "@angular/cdk/drag-drop";
import { CommonModule } from '@angular/common';
import { MapElement } from '../interfaces/MapElement';

@Component({
  selector: 'app-device',
  imports: [Service, CdkDrag, CommonModule],
  templateUrl: './device.html',
  styleUrl: './device.css',
})
export class Device extends MapElement {
  ip = input<string>("unknown");
  mac = input<string>("unknown");
  hostname = input<string>("unknown");
  status = input<string>("Unknown");
  services = input<Array<IService>>([]);
}

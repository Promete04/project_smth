import { Component, signal, computed } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { Device } from './device/device';
import { Router } from './router/router';
import { CdkDrag } from '@angular/cdk/drag-drop';
import dataJSON from './data.example.json';
import { IService } from './interfaces/IService';
import { IPosition } from './interfaces/IPosition';

interface Data {
  date: string;
  subnet: string;
  devices: Array<{
    ip: string;
    mac: string;
    hostname: string;
    status: 'Up' | 'Down' | 'Unknown';   
    services: Array<IService>
  }>;
}

interface Line {
  x1: number;
  x2: number;
  y1: number;
  y2: number;
}

@Component({
  selector: 'app-root',
  imports: [RouterOutlet, Device, Router, CdkDrag],
  templateUrl: './app.html',
  styleUrl: './app.css'
})
export class App {
  protected readonly title = signal('project-smth');
  data = dataJSON as Data;

  devicePositions = signal<Map<string, IPosition>>(new Map());
  routerPos = signal<IPosition | null>(null);
  
  /**
   * Create lines when positions change
   */
  lines = computed(() => {
    const router = this.routerPos();
    if (!router) return [];

    const newLines: Line[] = [];
    this.devicePositions().forEach((pos, ip) => {
      newLines.push({
        x1: router.x,
        y1: router.y,
        x2: pos.x,
        y2: pos.y
      });
    });
    return newLines;
  });

  /**
   * Sets router position
   */
  onRouterPosition(pos: IPosition) {
    this.routerPos.set(pos);
  }

  /**
   * Sets device position
   */
  onDevicePosition(ip: string, pos: IPosition) {
    const currentMap = new Map(this.devicePositions());
    currentMap.set(ip, pos);
    this.devicePositions.set(currentMap);
  }
}

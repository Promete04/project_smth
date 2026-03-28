import { Component, signal } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { Device } from './device/device';
import { Router } from './router/router';
import { CdkDrag } from '@angular/cdk/drag-drop';
import dataJSON from './data.example.json';
import { IService } from './interfaces/IService';

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

@Component({
  selector: 'app-root',
  imports: [RouterOutlet, Device, Router, CdkDrag],
  templateUrl: './app.html',
  styleUrl: './app.css'
})
export class App {
  protected readonly title = signal('project-smth');

  data = dataJSON as Data;
}
